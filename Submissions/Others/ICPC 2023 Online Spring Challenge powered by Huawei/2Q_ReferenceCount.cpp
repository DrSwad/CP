#include <bits/stdc++.h>
using namespace std;

const int MAX_TENANTS = 10;
const int MAX_BUFFER_SIZE = 1e6;
const int MAX_OPERATIONS = 1e6;
const int MAX_BAD_PRIORITY = 10;
const int MAX_DB_SIZE = 1e5;
const int MAX_TENANT_BUFFER_SIZE = 1e5;
const int MAX_ACCESS_TIME = 2e9;

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

  int frequent_capacity, recent_capacity, ghost_capacity;
  set<pair<int, Key>> frequent_keys, recent_keys, ghost_keys;

  set<pair<int, Key>> tenant_keys_in_frequent[MAX_TENANTS + 1];
  set<pair<int, Key>> tenant_keys_in_recent[MAX_TENANTS + 1];

  bool is_key_frequent[MAX_TENANTS + 1][MAX_DB_SIZE + 1];
  bool is_key_recent[MAX_TENANTS + 1][MAX_DB_SIZE + 1];
  bool is_key_ghost[MAX_TENANTS + 1][MAX_DB_SIZE + 1];

  const int max_key_reference_count = 6;
  int key_reference_count[MAX_TENANTS + 1][MAX_DB_SIZE + 1];
  int key_position_in_buffer[MAX_TENANTS + 1][MAX_DB_SIZE + 1];
  int key_last_access_time[MAX_TENANTS + 1][MAX_DB_SIZE + 1];

  int access_timer = 0;

  void initialize() {
    frequent_capacity = max(1, (total_buffer_size + 2) / 3);
    recent_capacity = total_buffer_size - frequent_capacity;
    ghost_capacity = total_buffer_size - recent_capacity;
  }

  void add_key_to_frequent(Key key) {
    auto [tenant, page] = key;
    assert(!is_key_frequent[tenant][page]);
    frequent_keys.insert(make_pair(key_last_access_time[tenant][page], key));
    tenant_keys_in_frequent[tenant].insert(make_pair(key_last_access_time[tenant][page], key));
    is_key_frequent[tenant][page] = true;
  }

  void remove_key_from_frequent(Key key) {
    auto [tenant, page] = key;
    assert(is_key_frequent[tenant][page]);
    frequent_keys.erase(make_pair(key_last_access_time[tenant][page], key));
    tenant_keys_in_frequent[tenant].erase(make_pair(key_last_access_time[tenant][page], key));
    is_key_frequent[tenant][page] = false;
  }

  void add_key_to_recent(Key key) {
    auto [tenant, page] = key;
    assert(!is_key_recent[tenant][page]);
    recent_keys.insert(make_pair(key_last_access_time[tenant][page], key));
    tenant_keys_in_recent[tenant].insert(make_pair(key_last_access_time[tenant][page], key));
    is_key_recent[tenant][page] = true;
  }

  void remove_key_from_recent(Key key) {
    auto [tenant, page] = key;
    assert(is_key_recent[tenant][page]);
    recent_keys.erase(make_pair(key_last_access_time[tenant][page], key));
    tenant_keys_in_recent[tenant].erase(make_pair(key_last_access_time[tenant][page], key));
    is_key_recent[tenant][page] = false;
  }

  void add_key_to_ghost(Key key) {
    auto [tenant, page] = key;
    assert(!is_key_ghost[tenant][page]);
    ghost_keys.insert(make_pair(key_last_access_time[tenant][page], key));
    is_key_ghost[tenant][page] = true;
  }

  void remove_key_from_ghost(Key key) {
    auto [tenant, page] = key;
    assert(is_key_ghost[tenant][page]);
    ghost_keys.erase(make_pair(key_last_access_time[tenant][page], key));
    is_key_ghost[tenant][page] = false;
  }

  void remove_key_from_buffer(Key key) {
    auto [tenant, page] = key;
    assert(tenant != -1 and page != -1);
    if (is_key_frequent[tenant][page]) remove_key_from_frequent(key);
    else if (is_key_recent[tenant][page]) remove_key_from_recent(key);
    else assert(false);
  }

  Key evict_some_key(vector<int> can_evict_from_tenants) {
    int min_access_time = MAX_ACCESS_TIME + 1;
    Key key(-1, -1);

    for (int t : can_evict_from_tenants) {
      if (!tenant_keys_in_recent[t].empty()) {
        while (true) {
          auto [cur_access_time, cur_key] = *tenant_keys_in_recent[t].begin();
          auto [cur_tenant, cur_page] = cur_key;
          if (key_reference_count[cur_tenant][cur_page] > 0) {
            key_reference_count[cur_tenant][cur_page]--;
            remove_key_from_recent(cur_key);
            key_last_access_time[cur_tenant][cur_page] = ++access_timer;
            add_key_to_recent(cur_key);
          }
          else {
            if (cur_access_time < min_access_time) {
              min_access_time = cur_access_time;
              key = cur_key;
            }
            break;
          }
        }
      }
    }

    if (key.first == -1) {
      for (int t : can_evict_from_tenants) {
        if (!tenant_keys_in_frequent[t].empty()) {
          while (true) {
            auto [cur_access_time, cur_key] = *tenant_keys_in_frequent[t].begin();
            auto [cur_tenant, cur_page] = cur_key;
            if (key_reference_count[cur_tenant][cur_page] > 0) {
              key_reference_count[cur_tenant][cur_page]--;
              remove_key_from_frequent(cur_key);
              key_last_access_time[cur_tenant][cur_page] = ++access_timer;
              add_key_to_frequent(cur_key);
            }
            else {
              auto [cur_access_time, cur_key] = *tenant_keys_in_frequent[t].begin();
              if (cur_access_time < min_access_time) {
                min_access_time = cur_access_time;
                key = cur_key;
              }
              break;
            }
          }
        }
      }
    }

    assert(key.first != -1);

    return key;
  }

  void balance_buffer_lists() {
    if ((int)frequent_keys.size() > frequent_capacity) {
      auto [access_time, key] = *frequent_keys.begin();
      remove_key_from_frequent(key);
      add_key_to_recent(key);
    }

    if ((int)recent_keys.size() > recent_capacity) {
      auto [access_time, key] = *recent_keys.begin();
      remove_key_from_recent(key);
      add_key_to_frequent(key);
    }

    assert((int)frequent_keys.size() <= frequent_capacity);
    assert((int)recent_keys.size() <= recent_capacity);
  }

  int handle_operation(int tenant, int page) {
    Key key(tenant, page);
    access_timer++;

    if (is_key_frequent[tenant][page] or is_key_recent[tenant][page]) {
      // cerr << "Key is already in buffer" << endl;

      remove_key_from_buffer(key);
      key_last_access_time[tenant][page] = access_timer;
      key_reference_count[tenant][page] = min(key_reference_count[tenant][page] + 1, max_key_reference_count);
      add_key_to_frequent(key);
      balance_buffer_lists();

      assert(key_position_in_buffer[tenant][page] != 0);
    }
    else {
      // if (is_key_ghost[tenant][page]) cerr << "Key is in ghost" << endl;
      // else cerr << "Key doesn't exist in buffer or ghost" << endl;

      bool must_evict_some_key = false;
      vector<int> can_evict_from_tenants;
      if ((int)tenant_keys_in_frequent[tenant].size() + (int)tenant_keys_in_recent[tenant].size() >= buffer_max_sizes[tenant]) {
        must_evict_some_key = true;
        can_evict_from_tenants.push_back(tenant);
      }
      else if ((int)frequent_keys.size() + (int)recent_keys.size() >= total_buffer_size) {
        must_evict_some_key = true;
        for (int t = 1; t <= total_tenants; t++) {
          if ((int)tenant_keys_in_frequent[t].size() + (int)tenant_keys_in_recent[t].size() > buffer_min_sizes[t] - (t == tenant)) {
            can_evict_from_tenants.push_back(t);
          }
        }
      }

      if (must_evict_some_key) {
        assert(!can_evict_from_tenants.empty());

        Key evicted_key = evict_some_key(can_evict_from_tenants);
        remove_key_from_buffer(evicted_key);

        auto [evicted_tenant, evicted_page] = evicted_key;
        assert(evicted_tenant != -1);
        key_position_in_buffer[tenant][page] = key_position_in_buffer[evicted_tenant][evicted_page];
        key_position_in_buffer[evicted_tenant][evicted_page] = 0;

        add_key_to_ghost(evicted_key);
        if (ghost_keys.size() > ghost_capacity) {
          remove_key_from_ghost(ghost_keys.begin()->second);
        }
      }
      else {
        assert(can_evict_from_tenants.empty());
        assert((int)frequent_keys.size() + (int)recent_keys.size() < total_buffer_size);
        key_position_in_buffer[tenant][page] = (int)frequent_keys.size() + (int)recent_keys.size() + 1;
      }

      if (is_key_ghost[tenant][page]) {
        remove_key_from_ghost(make_pair(tenant, page));
        if (ghost_keys.size() > ghost_capacity) {
          remove_key_from_ghost(ghost_keys.begin()->second);
        }
        key_last_access_time[tenant][page] = access_timer;
        add_key_to_frequent(key);
      }
      else {
        key_last_access_time[tenant][page] = access_timer;
        add_key_to_recent(key);
      }

      balance_buffer_lists();

      assert(key_position_in_buffer[tenant][page] != 0);
    }

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

  ReplacementAlgorithm::initialize();

  for (int operation_id = 1; operation_id <= total_operations; operation_id++) {
    int tenant, page;
    cin >> tenant >> page;

    cout << ReplacementAlgorithm::handle_operation(tenant, page) << endl;
  } 

  return 0;
}
