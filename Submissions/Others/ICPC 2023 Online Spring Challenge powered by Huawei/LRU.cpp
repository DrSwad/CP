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
  queue<pair<int, int>> queue_of_tenant_pages[MAX_TENANTS + 1];

  int operations_processed = 0;
  int buffer_positions_used = 0;
  int page_last_access[MAX_TENANTS + 1][MAX_DB_SIZE + 1];
  int page_position_in_buffer[MAX_TENANTS + 1][MAX_DB_SIZE + 1];

  void remove_expired_from_queue(int tenant) {
    while (!queue_of_tenant_pages[tenant].empty()) {
      auto [cur_page, cur_operation_id] = queue_of_tenant_pages[tenant].front();
      if (page_last_access[tenant][cur_page] != cur_operation_id or
          page_position_in_buffer[tenant][cur_page] == 0) {
        queue_of_tenant_pages[tenant].pop();
      }
      else {
        break;
      }
    }
  }

  int get_LRU_page(int tenant) {
      remove_expired_from_queue(tenant);
      if (queue_of_tenant_pages[tenant].empty()) return 0;
      return queue_of_tenant_pages[tenant].front().first;
  }

  int handle_operation(int tenant, int page) {
    operations_processed++;
    page_last_access[tenant][page] = operations_processed;
    queue_of_tenant_pages[tenant].emplace(page, operations_processed);

    if (page_position_in_buffer[tenant][page] != 0) {
      // cerr << "Page already exists" << endl;
      return page_position_in_buffer[tenant][page];
    }

    if (tenant_current_buffer_size[tenant] >= buffer_max_sizes[tenant]) {
      // cerr << "Page must replace own tenant's page" << endl;
      int LRU_page = get_LRU_page(tenant);
      assert(LRU_page != 0);

      int at_buffer_position = page_position_in_buffer[tenant][LRU_page];
      page_position_in_buffer[tenant][LRU_page] = 0;
      page_position_in_buffer[tenant][page] = at_buffer_position;

      return page_position_in_buffer[tenant][page];
    }
    else {
      if (buffer_positions_used < total_buffer_size) {
        // cerr << "Empty buffer available" << endl;
        buffer_positions_used++;     
        page_position_in_buffer[tenant][page] = buffer_positions_used;
        tenant_current_buffer_size[tenant]++;
        return page_position_in_buffer[tenant][page];
      }
      else {
        // cerr << "Replace LRU" << endl;
        int earliest_access_time = MAX_OPERATIONS + 1;
        pair<int, int> earliest_accessed_page;

        for (int t = 1; t <= total_tenants; t++) {
          if (tenant_current_buffer_size[t] <= buffer_min_sizes[t] - (t == tenant)) {
            continue;
          }

          int LRU_page = get_LRU_page(t);
          if (LRU_page == 0) continue;

          if (page_last_access[t][LRU_page] < earliest_access_time) {
            earliest_access_time = page_last_access[t][LRU_page];
            earliest_accessed_page = make_pair(t, LRU_page);
          }
        }

        assert(earliest_access_time <= MAX_OPERATIONS);

        auto [LRU_tenant, LRU_page] = earliest_accessed_page;

        tenant_current_buffer_size[LRU_tenant]--;
        tenant_current_buffer_size[tenant]++;

        int at_buffer_position = page_position_in_buffer[LRU_tenant][LRU_page];
        page_position_in_buffer[LRU_tenant][LRU_page] = 0;
        page_position_in_buffer[tenant][page] = at_buffer_position;

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
