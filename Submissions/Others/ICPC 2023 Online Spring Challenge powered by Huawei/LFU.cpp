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
  set<pair<int, int>> set_of_tenant_pages[MAX_TENANTS + 1];

  int buffer_positions_used = 0;
  int page_position_in_buffer[MAX_TENANTS + 1][MAX_DB_SIZE + 1];
  int page_frequency_count[MAX_TENANTS + 1][MAX_DB_SIZE + 1];

  int handle_operation(int tenant, int page) {
    if (page_position_in_buffer[tenant][page] != 0) {
      cerr << "Page already exists" << endl;
      set_of_tenant_pages[tenant].erase(make_pair(page_frequency_count[tenant][page], page));
      page_frequency_count[tenant][page]++;
      set_of_tenant_pages[tenant].insert(make_pair(page_frequency_count[tenant][page], page));
      return page_position_in_buffer[tenant][page];
    }

    if (tenant_current_buffer_size[tenant] >= buffer_max_sizes[tenant]) {
      cerr << "Page must replace own tenant's page" << endl;
      assert(!set_of_tenant_pages[tenant].empty());
      int LFU_page = set_of_tenant_pages[tenant].begin()->second;
      set_of_tenant_pages[tenant].erase(set_of_tenant_pages[tenant].begin());

      int at_buffer_position = page_position_in_buffer[tenant][LFU_page];
      page_position_in_buffer[tenant][LFU_page] = 0;
      page_position_in_buffer[tenant][page] = at_buffer_position;

      page_frequency_count[tenant][page]++;
      set_of_tenant_pages[tenant].insert(make_pair(page_frequency_count[tenant][page], page));

      return page_position_in_buffer[tenant][page];
    }
    else {
      if (buffer_positions_used < total_buffer_size) {
        cerr << "Empty buffer available" << endl;
        buffer_positions_used++;     
        page_position_in_buffer[tenant][page] = buffer_positions_used;
        tenant_current_buffer_size[tenant]++;
        page_frequency_count[tenant][page]++;
        set_of_tenant_pages[tenant].insert(make_pair(page_frequency_count[tenant][page], page));
        return page_position_in_buffer[tenant][page];
      }
      else {
        cerr << "Replace LFU" << endl;
        int least_frequent_access = MAX_OPERATIONS + 1;
        pair<int, int> least_accessed_page;

        for (int t = 1; t <= total_tenants; t++) {
          if (tenant_current_buffer_size[t] <= buffer_min_sizes[t] - (t == tenant)) {
            continue;
          }

          if (set_of_tenant_pages[t].empty()) continue;
          int LFU_page = set_of_tenant_pages[t].begin()->second;

          if (page_frequency_count[t][LFU_page] < least_frequent_access) {
            least_frequent_access = page_frequency_count[t][LFU_page];
            least_accessed_page = make_pair(t, LFU_page);
          }
        }

        assert(least_frequent_access <= MAX_OPERATIONS);

        auto [LFU_tenant, LFU_page] = least_accessed_page;

        set_of_tenant_pages[LFU_tenant].erase(make_pair(page_frequency_count[LFU_tenant][LFU_page], LFU_page));

        tenant_current_buffer_size[LFU_tenant]--;
        tenant_current_buffer_size[tenant]++;

        int at_buffer_position = page_position_in_buffer[LFU_tenant][LFU_page];
        page_position_in_buffer[LFU_tenant][LFU_page] = 0;
        page_position_in_buffer[tenant][page] = at_buffer_position;

        page_frequency_count[tenant][page]++;
        set_of_tenant_pages[tenant].insert(make_pair(page_frequency_count[tenant][page], page));

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
