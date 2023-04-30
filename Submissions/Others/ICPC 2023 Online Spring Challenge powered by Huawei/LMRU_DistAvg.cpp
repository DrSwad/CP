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

  long long total_page_operation_distance = 0;
  int reaccess_operations = 0;

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
      remove_expired_from_deque(tenant, LRU);
      if (deque_of_tenant_pages[tenant].empty()) return 0;
      return LRU ? deque_of_tenant_pages[tenant].front().first : deque_of_tenant_pages[tenant].back().first;
  }

  int handle_operation(int tenant, int page) {
    operations_processed++;

    bool LRU;
    if (page_last_access[tenant][page] != 0) {
      int dist = operations_processed - page_last_access[tenant][page];
      total_page_operation_distance += dist;
      reaccess_operations++;
      double average_distance = total_page_operation_distance / (double)reaccess_operations;
      LRU = average_distance <= total_buffer_size / (double)2;
    }

    page_last_access[tenant][page] = operations_processed;

    if (page_position_in_buffer[tenant][page] != 0) {
      // cerr << "Page already exists" << endl;
      deque_of_tenant_pages[tenant].emplace_back(page, operations_processed);
      return page_position_in_buffer[tenant][page];
    }

    if (tenant_current_buffer_size[tenant] >= buffer_max_sizes[tenant]) {
      // cerr << "Page must replace own tenant's page" << endl;
      int RU_page = get_RU_page(tenant, LRU);
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

  for (int operation_id = 1; operation_id <= total_operations; operation_id++) {
    int tenant, page;
    cin >> tenant >> page;

    cout << ReplacementAlgorithm::handle_operation(tenant, page) << endl;
  } 

  return 0;
}
