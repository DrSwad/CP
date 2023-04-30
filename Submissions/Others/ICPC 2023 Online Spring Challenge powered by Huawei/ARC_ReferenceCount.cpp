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
  typedef pair<int, int> Key;
  typedef int Page;

  list<Key> T[2], B[2];
  list<Page> tenant_keys_in_T[MAX_TENANTS + 1][2];
  list<Page> tenant_keys_in_B[MAX_TENANTS + 1][2];
  int T0_ideal_size = 0;

  bool is_key_in_T[MAX_TENANTS + 1][MAX_DB_SIZE + 1][2];
  list<Key>::iterator key_in_T[MAX_TENANTS + 1][MAX_DB_SIZE + 1][2];
  list<Page>::iterator key_in_tenant_T[MAX_TENANTS + 1][MAX_DB_SIZE + 1][2];

  bool is_key_in_B[MAX_TENANTS + 1][MAX_DB_SIZE + 1][2];
  list<Key>::iterator key_in_B[MAX_TENANTS + 1][MAX_DB_SIZE + 1][2];
  list<Page>::iterator key_in_tenant_B[MAX_TENANTS + 1][MAX_DB_SIZE + 1][2];

  const int max_key_reference_count = 6;
  int key_reference_count[MAX_TENANTS + 1][MAX_DB_SIZE + 1];
  int key_position_in_buffer[MAX_TENANTS + 1][MAX_DB_SIZE + 1];
  int key_last_access_operation_id[MAX_TENANTS + 1][MAX_DB_SIZE + 1];
  int operations_processed = 0;

  void add_key_to_T(Key key, int index) {
    auto [tenant, page] = key;

    assert(!is_key_in_T[tenant][page][index]);
    key_in_T[tenant][page][index] = T[index].insert(T[index].end(), key);
    key_in_tenant_T[tenant][page][index] = tenant_keys_in_T[tenant][index].insert(tenant_keys_in_T[tenant][index].end(), page);
    is_key_in_T[tenant][page][index] = true;

    key_reference_count[tenant][page] = index == 0 ? 1 : 2;
  }

  void remove_key_from_T(Key key, int index) {
    auto [tenant, page] = key;

    assert(is_key_in_T[tenant][page][index]);
    T[index].erase(key_in_T[tenant][page][index]);
    tenant_keys_in_T[tenant][index].erase(key_in_tenant_T[tenant][page][index]);
    is_key_in_T[tenant][page][index] = false;
  }

  void add_key_to_B(Key key, int index) {
    auto [tenant, page] = key;

    assert(!is_key_in_B[tenant][page][index]);
    key_in_B[tenant][page][index] = B[index].insert(B[index].end(), key);
    key_in_tenant_B[tenant][page][index] = tenant_keys_in_B[tenant][index].insert(tenant_keys_in_B[tenant][index].end(), page);
    is_key_in_B[tenant][page][index] = true;
  }

  void remove_key_from_B(Key key, int index) {
    auto [tenant, page] = key;

    assert(is_key_in_B[tenant][page][index]);
    B[index].erase(key_in_B[tenant][page][index]);
    tenant_keys_in_B[tenant][index].erase(key_in_tenant_B[tenant][page][index]);
    is_key_in_B[tenant][page][index] = false;
  }

  int get_earliest_page_of_tenant_from_T(int index, int tenant) {
    assert(!tenant_keys_in_T[tenant][index].empty());
    int page;

    while (true) {
      page = tenant_keys_in_T[tenant][index].front();
      if (key_reference_count[tenant][page] <= 2) break;
      else {
        int old_key_reference_count = key_reference_count[tenant][page];
        remove_key_from_T(Key(tenant, page), index);
        add_key_to_T(Key(tenant, page), index);
        key_reference_count[tenant][page] = old_key_reference_count - 1;
      }
    }

    return page;
  }

  Key evict_some_page_from_T(int index, vector<int> can_evict_from_tenants) {
    int min_operation_id = MAX_OPERATIONS + 1;
    Key key(-1, -1);

    for (int t : can_evict_from_tenants) {
      if (!tenant_keys_in_T[t][index].empty()) {
        int page = get_earliest_page_of_tenant_from_T(index, t);
        int cur_operation_id = key_last_access_operation_id[t][page];
        if (cur_operation_id < min_operation_id) {
          min_operation_id = cur_operation_id;
          Key cur_key(t, page);
          key = cur_key;
        }
      }
    }

    return key;
  }

  Key evict_some_page(vector<int> can_evict_from_tenants) {
    Key key(-1, -1);

    if (!T[0].empty() and (T[1].empty() or (int)T[0].size() > T0_ideal_size)) {
      key = evict_some_page_from_T(0, can_evict_from_tenants);
    }

    if (key.first == -1) {
      key = evict_some_page_from_T(1, can_evict_from_tenants);
      assert(key.first != -1);
    }

    return key;
  }

  void move_buffer_key_to_ghost(Key key) {
    auto [tenant, page] = key;
    key_position_in_buffer[tenant][page] = 0;
    for (int index = 0; index < 2; index++) {
      if (is_key_in_T[tenant][page][index]) {
        remove_key_from_T(key, index);
        add_key_to_B(key, index);
        return;
      }
    }
    assert(false);
  }

  int handle_operation(int tenant, int page) {
    Key key(tenant, page);
    key_last_access_operation_id[tenant][page] = ++operations_processed;

    int add_to_T0_ideal_size = 0;

    if (is_key_in_T[tenant][page][0] or is_key_in_T[tenant][page][1]) {
      // cerr << "Key is already in buffer" << endl;
      int index = is_key_in_T[tenant][page][0] ? 0 : 1;

      remove_key_from_T(key, index);
      int old_key_reference_count = key_reference_count[tenant][page];
      add_key_to_T(key, 1);
      key_reference_count[tenant][page] = old_key_reference_count + 1;

      if (index == 0) add_to_T0_ideal_size = 1;
      else add_to_T0_ideal_size = -1;

      assert(key_position_in_buffer[tenant][page] != 0);
    }
    else {
      int add_to_list = 0;
      if (is_key_in_B[tenant][page][0] or is_key_in_B[tenant][page][1]) {
        add_to_list = 1;
        if (is_key_in_B[tenant][page][0]) {
          // cerr << "Key is in ghost 0" << endl;
          add_to_T0_ideal_size = 1;
          remove_key_from_B(key, 0);
        }
        else {
          assert(is_key_in_B[tenant][page][1]);
          // cerr << "Key is in ghost 1" << endl;
          add_to_T0_ideal_size = -1;
          remove_key_from_B(key, 1);
        }
      }
      // else cerr << "Key doesn't exist in buffer or ghost" << endl;

      vector<int> can_evict_from_tenants;
      if ((int)tenant_keys_in_T[tenant][0].size() + (int)tenant_keys_in_T[tenant][1].size() >= buffer_max_sizes[tenant]) {
        can_evict_from_tenants.push_back(tenant);
      }
      else if ((int)T[0].size() + (int)T[1].size() >= total_buffer_size) {
        for (int t = 1; t <= total_tenants; t++) {
          if ((int)tenant_keys_in_T[t][0].size() + (int)tenant_keys_in_T[t][1].size() > buffer_min_sizes[t] - (t == tenant)) {
            can_evict_from_tenants.push_back(t);
          }
        }
      }

      if (!can_evict_from_tenants.empty()) {
        Key evicted_key = evict_some_page(can_evict_from_tenants);
        auto [evicted_tenant, evicted_page] = evicted_key;
        assert(evicted_tenant != -1);

        key_position_in_buffer[tenant][page] = key_position_in_buffer[evicted_tenant][evicted_page];
        move_buffer_key_to_ghost(evicted_key);

        int ghost_index;
        if (is_key_in_B[evicted_tenant][evicted_page][0]) ghost_index = 0;
        else if (is_key_in_B[evicted_tenant][evicted_page][1]) ghost_index = 1;
        else assert(false);

        if ((int)B[ghost_index].size() > total_buffer_size) {
          remove_key_from_B(B[ghost_index].front(), ghost_index);
        }
      }
      else {
        assert((int)T[0].size() + (int)T[1].size() < total_buffer_size);
        key_position_in_buffer[tenant][page] = (int)T[0].size() + (int)T[1].size() + 1;
      }

      add_key_to_T(key, add_to_list);

      assert(key_position_in_buffer[tenant][page] != 0);
    }

    T0_ideal_size = clamp(T0_ideal_size + add_to_T0_ideal_size, 0, (int)T[0].size() + (int)T[1].size());
    return key_position_in_buffer[tenant][page];
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
