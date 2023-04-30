#include <bits/stdc++.h>
using namespace std;

const int MAX_TENANTS = 10;
const int MAX_BUFFER_SIZE = 1e6;
const int MAX_OPERATIONS = 1e6;
const int MAX_BAD_PRIORITY = 10;
const int MAX_DB_SIZE = 1e5;
const int MAX_TENANT_BUFFER_SIZE = 1e5;

int total_tenants;
int total_buffer_size;
int total_operations;

int bad_priorities[MAX_TENANTS + 1];
int db_sizes[MAX_TENANTS + 1];

int buffer_min_sizes[MAX_TENANTS + 1];
int buffer_base_sizes[MAX_TENANTS + 1];
int buffer_max_sizes[MAX_TENANTS + 1];

namespace ReplacementAlgorithm {
  int tenant_current_buffer_size[MAX_TENANTS + 1];
  deque<pair<int, int>> deque_of_tenant_pages[MAX_TENANTS + 1];

  int operations_processed = 0;
  int buffer_positions_used = 0;
  int page_last_access[MAX_TENANTS + 1][MAX_DB_SIZE + 1];
  int page_position_in_buffer[MAX_TENANTS + 1][MAX_DB_SIZE + 1];
  int page_reference_count[MAX_TENANTS + 1][MAX_DB_SIZE + 1];
  const int max_page_reference_count = 6;

  bool LRU_current_choice;
  int hits = 0;
  int faults = 0;
  const double hit_fault_ratio_to_switch = 1.075;
  map<pair<int, int>, bool> found_keys;
  int max_hits_tracked;
  deque<bool> latest_hits_tracker;
  queue<double> latest_ratio_tracker;

  void initialize() {
    // max_hits_tracked = max(1, total_buffer_size / 2);
    max_hits_tracked = 1000;
    LRU_current_choice = true;
    latest_ratio_tracker.push(hit_fault_ratio_to_switch);
  }

  void remove_expired_from_deque(int tenant, bool front) {
    while (!deque_of_tenant_pages[tenant].empty()) {
      auto [cur_page, cur_operation_id] = front ? deque_of_tenant_pages[tenant].front() : deque_of_tenant_pages[tenant].back();
      if (page_last_access[tenant][cur_page] != cur_operation_id or
          page_position_in_buffer[tenant][cur_page] == 0) {
        if (front) deque_of_tenant_pages[tenant].pop_front();
        else deque_of_tenant_pages[tenant].pop_back();
      }
      else {
        break;
      }
    }
  }

  int get_RU_page(int tenant, bool LRU) {
    while (true) {
      remove_expired_from_deque(tenant, LRU);
      if (deque_of_tenant_pages[tenant].empty()) return 0;
      auto [page, operation_id] = LRU ? deque_of_tenant_pages[tenant].front() : deque_of_tenant_pages[tenant].back();
      if (page_reference_count[tenant][page] == 0) return page;
      else {
        if (LRU) {
          deque_of_tenant_pages[tenant].push_back(deque_of_tenant_pages[tenant].front());
          deque_of_tenant_pages[tenant].pop_front();
        }
        else {
          deque_of_tenant_pages[tenant].push_front(deque_of_tenant_pages[tenant].back());
          deque_of_tenant_pages[tenant].pop_back();
        }
        page_reference_count[tenant][page]--;
      }
    }
  }

  int handle_operation(int tenant, int page) {
    operations_processed++;
    page_last_access[tenant][page] = operations_processed;

    if (page_position_in_buffer[tenant][page] != 0) {
      // cerr << "Page already exists" << endl
      if (LRU_current_choice) {
        page_reference_count[tenant][page] = min(page_reference_count[tenant][page] + 1, max_page_reference_count);
      }

      if (buffer_positions_used >= total_buffer_size) {
        if (found_keys.find(make_pair(tenant, page)) != found_keys.end()) {
          latest_hits_tracker.push_back(true);
          hits++;
          if (latest_hits_tracker.size() > max_hits_tracked) {
            if (latest_hits_tracker.front()) hits--;
            else faults--;
            latest_hits_tracker.pop_front();
          }
        }
      }

      deque_of_tenant_pages[tenant].emplace_back(page, operations_processed);
      found_keys[make_pair(tenant, page)] = true;
      return page_position_in_buffer[tenant][page];
    }

    if (buffer_positions_used >= total_buffer_size) {
      if (found_keys.find(make_pair(tenant, page)) != found_keys.end()) {
        latest_hits_tracker.push_back(false);
        faults++;
        if (latest_hits_tracker.size() > max_hits_tracked) {
          if (latest_hits_tracker.front()) hits--;
          else faults--;
          latest_hits_tracker.pop_front();
        }
      }
      if (LRU_current_choice and latest_hits_tracker.size() >= max_hits_tracked and (double)hits / faults < latest_ratio_tracker.front()) {
        LRU_current_choice = !LRU_current_choice;
        latest_ratio_tracker.push((double)hits / faults);
        hits = faults = 0;
        found_keys.clear();
        latest_hits_tracker = deque<bool>();

        for (int t = 1; t <= total_tenants; t++) {
          for (int page = 1; page <= db_sizes[t]; page++) {
            page_reference_count[t][page] = 0;
          }
        }
      }
    }

    found_keys[make_pair(tenant, page)] = true;

    if (tenant_current_buffer_size[tenant] >= buffer_max_sizes[tenant]) {
      // cerr << "Page must replace own tenant's page" << endl;
      int RU_page = get_RU_page(tenant, LRU_current_choice);
      assert(RU_page != 0);

      int at_buffer_position = page_position_in_buffer[tenant][RU_page];
      page_position_in_buffer[tenant][RU_page] = 0;
      page_position_in_buffer[tenant][page] = at_buffer_position;

      deque_of_tenant_pages[tenant].emplace_back(page, operations_processed);
      return page_position_in_buffer[tenant][page];
    }
    else {
      if (buffer_positions_used < total_buffer_size) {
        // cerr << "Empty buffer available" << endl;
        buffer_positions_used++;     
        page_position_in_buffer[tenant][page] = buffer_positions_used;
        tenant_current_buffer_size[tenant]++;

        deque_of_tenant_pages[tenant].emplace_back(page, operations_processed);
        return page_position_in_buffer[tenant][page];
      }
      else {
        // cerr << "Replace RU" << endl;
        bool LRU = LRU_current_choice;

        int RU_access_time = LRU ? MAX_OPERATIONS + 1 : 0;
        pair<int, int> RU_accessed_page;

        for (int t = 1; t <= total_tenants; t++) {
          if (tenant_current_buffer_size[t] <= buffer_min_sizes[t] - (t == tenant)) {
            continue;
          }

          int RU_page = get_RU_page(t, LRU);
          if (RU_page == 0) continue;

          if ((LRU and page_last_access[t][RU_page] < RU_access_time) or
              (!LRU and page_last_access[t][RU_page] > RU_access_time)) {
            RU_access_time = page_last_access[t][RU_page];
            RU_accessed_page = make_pair(t, RU_page);
          }
        }

        assert((LRU and RU_access_time <= MAX_OPERATIONS) or (!LRU and RU_access_time > 0));

        auto [RU_tenant, RU_page] = RU_accessed_page;

        tenant_current_buffer_size[RU_tenant]--;
        tenant_current_buffer_size[tenant]++;

        int at_buffer_position = page_position_in_buffer[RU_tenant][RU_page];
        page_position_in_buffer[RU_tenant][RU_page] = 0;
        page_position_in_buffer[tenant][page] = at_buffer_position;

        deque_of_tenant_pages[tenant].emplace_back(page, operations_processed);
        return page_position_in_buffer[tenant][page];
      }
    }
  }
}

int main() {
  cin >> total_tenants;
  cin >> total_buffer_size;
  cin >> total_operations;

  for (int t = 1; t <= total_tenants; t++) {
    cin >> bad_priorities[t];
  }

  for (int t = 1; t <= total_tenants; t++) {
    cin >> db_sizes[t];
  }

  for (int t = 1; t <= total_tenants; t++) {
    cin >> buffer_min_sizes[t];
    cin >> buffer_base_sizes[t];
    cin >> buffer_max_sizes[t];
  }

  ReplacementAlgorithm::initialize();

  for (int operation_id = 1; operation_id <= total_operations; operation_id++) {
    int tenant, page;
    cin >> tenant >> page;

    cout << ReplacementAlgorithm::handle_operation(tenant, page) << endl;
  } 

  return 0;
}
