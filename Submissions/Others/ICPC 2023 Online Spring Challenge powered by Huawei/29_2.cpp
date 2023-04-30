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

struct Node {
  int page_id = 0;
  bool active = false;
  int last_access_time = 0;
  int total_reference_count = 0;
  Node() {}
};
typedef function<bool(const Node&, const Node&)> Comparator;

class SegmentTree {
  int n;
  vector<Node> a;
  vector<int> st;
  Comparator compare;

  int merge(int stL, int stR) {
    if (stL == 0) return stR;
    else if (stR == 0) return stL;
    else if (compare(a[stL], a[stR])) return stL;
    else return stR;
  }
  void build(int stI, int L, int R) {
    if (L == R) {
      st[stI] = a[L].active ? L : 0;
      return;
    }
    int mid = (L + R) >> 1;
    build(stI << 1, L, mid);
    build(stI << 1 | 1, mid + 1, R);
    st[stI] = merge(st[stI << 1], st[stI << 1 | 1]);
  }
  void update(int stI, int L, int R, int at, Node val) {
    if (L == R) {
      a[L] = val;
      st[stI] = a[L].active ? L : 0;
      return;
    }
    int mid = (L + R) >> 1;
    if (at <= mid) update(stI << 1, L, mid, at, val);
    else update(stI << 1 | 1, mid + 1, R, at, val);
    st[stI] = merge(st[(stI << 1)], st[(stI << 1) + 1]);
  }
  int query(int stI, int L, int R, int l, int r) {
    if (l <= L && R <= r) return st[stI];
    int mid = (L + R) >> 1;
    if (r <= mid) return query(stI << 1, L, mid, l, r);
    else if (mid + 1 <= l) return query(stI << 1 | 1, mid + 1, R, l, r);
    else return merge(
        query(stI << 1, L, mid, l, mid),
        query(stI << 1 | 1, mid + 1, R, mid + 1, r)
        );
  }
public:
  SegmentTree(int _n) {
    n = _n;
    a.emplace_back();
    for (int i = 1; i <= n; i++) {
      a.emplace_back();
      a.back().page_id = i;
    }
    st.resize(4 * n + 1, 0);
  }
  void build(const Comparator &_compare) {
    compare = _compare;
    build(1, 1, n);
  }
  int query(int l, int r) { // range [l, r], 1-based index
    if (r < 1 || n < l || r < l) return 0;
    l = max(l, 1); r = min(r, n);
    return query(1, 1, n, l, r);
  }
  Node node(int at) { // at is 1-based index
    assert(1 <= at and at <= n);
    return a[at];
  }
  void update(int at, Node val) { // at is 1-based index
    if (at < 1 || n < at) return;
    update(1, 1, n, at, val);
  }
};

class AlgorithmTemplate {
public:
  // tenant properties
  int tenant_current_buffer_size[MAX_TENANTS + 1];
  vector<SegmentTree> segtree_of_tenant_pages;

  // page properties
  int page_position_in_buffer[MAX_TENANTS + 1][MAX_DB_SIZE + 1];
  int page_buffer_hit_count[MAX_TENANTS + 1][MAX_DB_SIZE + 1];
  int page_real_access_time[MAX_TENANTS + 1][MAX_DB_SIZE + 1];
  const int max_page_buffer_hit_count = 6;

  // general properties
  int access_timer = 0;
  int buffer_positions_used = 0;
  
  // algorithm properties
  Comparator compare;
  bool use_page_buffer_hit_count;

  AlgorithmTemplate(Comparator compare, bool use_page_buffer_hit_count) {
    segtree_of_tenant_pages.emplace_back(1);
    for (int t = 1; t <= total_tenants; t++) {
      segtree_of_tenant_pages.emplace_back(db_sizes[t]);
    }
    update_comparator(compare, use_page_buffer_hit_count);
  }
  
  void update_comparator(Comparator _compare, bool _use_page_buffer_hit_count) {
    compare = _compare;
    use_page_buffer_hit_count = _use_page_buffer_hit_count;
    for (int t = 1; t <= total_tenants; t++) {
      segtree_of_tenant_pages[t].build(compare);
    }
  }

  int get_lowest_page(int tenant) {
    int page;

    while (true) {
      page = segtree_of_tenant_pages[tenant].query(1, db_sizes[tenant]);
      assert(page != 0);
      Node node = segtree_of_tenant_pages[tenant].node(page);

      if (!use_page_buffer_hit_count or page_buffer_hit_count[tenant][page] == 0) {
        if (page_real_access_time[tenant][page]) {
          node.last_access_time = page_real_access_time[tenant][page];
          segtree_of_tenant_pages[tenant].update(page, node);
        }
        break;
      }
      else {
        if (page_real_access_time[tenant][page] == 0) {
          page_real_access_time[tenant][page] = node.last_access_time;
        }
        node.last_access_time = ++access_timer;
        segtree_of_tenant_pages[tenant].update(page, node);
        page_buffer_hit_count[tenant][page]--;
      }
    }

    // page_buffer_hit_count[tenant][page] = 0;
    page_real_access_time[tenant][page] = 0;
    return page;
  }

  pair<int, bool> handle_operation(int tenant, int page) {
    bool got_hit = false;

    if (page_position_in_buffer[tenant][page] != 0) {
      // cerr << "Page already exists" << endl;
      
      got_hit = true;
      page_buffer_hit_count[tenant][page] = min(max_page_buffer_hit_count, page_buffer_hit_count[tenant][page] + 1);
      if (page_real_access_time[tenant][page]) {
        page_real_access_time[tenant][page] = 0;
      }

      // Update new node
      Node page_node = segtree_of_tenant_pages[tenant].node(page);
      page_node.last_access_time = ++access_timer;
      page_node.total_reference_count++;
      segtree_of_tenant_pages[tenant].update(page, page_node);
    }
    else if (tenant_current_buffer_size[tenant] >= buffer_max_sizes[tenant]) {
      // cerr << "Page must replace own tenant's page" << endl;

      int lowest_page = get_lowest_page(tenant);
      assert(lowest_page != 0);

      Node lowest_page_node = segtree_of_tenant_pages[tenant].node(lowest_page);
      lowest_page_node.active = false;
      segtree_of_tenant_pages[tenant].update(lowest_page, lowest_page_node);

      Node page_node = segtree_of_tenant_pages[tenant].node(page);
      page_node.active = true;
      page_node.last_access_time = ++access_timer;
      page_node.total_reference_count++;
      segtree_of_tenant_pages[tenant].update(page, page_node);

      int at_buffer_position = page_position_in_buffer[tenant][lowest_page];
      page_position_in_buffer[tenant][lowest_page] = 0;
      page_position_in_buffer[tenant][page] = at_buffer_position;
    }
    else if (buffer_positions_used < total_buffer_size) {
      // cerr << "Empty buffer available" << endl;

      Node page_node = segtree_of_tenant_pages[tenant].node(page);
      page_node.active = true;
      page_node.last_access_time = ++access_timer;
      page_node.total_reference_count++;
      segtree_of_tenant_pages[tenant].update(page, page_node);

      buffer_positions_used++;
      tenant_current_buffer_size[tenant]++;

      page_position_in_buffer[tenant][page] = buffer_positions_used;
    }
    else {
      // cerr << "Replace lowest page" << endl;

      bool found = false;
      pair<int, int> lowest_key;

      for (int t = 1; t <= total_tenants; t++) {
        if (tenant_current_buffer_size[t] <= buffer_min_sizes[t] - (t == tenant)) {
          continue;
        }

        int cur_lowest_page = get_lowest_page(t);
        assert(cur_lowest_page != 0);

        auto [lowest_tenant, lowest_page] = lowest_key;

        if (!found or compare(segtree_of_tenant_pages[t].node(cur_lowest_page), segtree_of_tenant_pages[lowest_tenant].node(lowest_page))) {
          lowest_key = make_pair(t, cur_lowest_page);
          found = true;
        }
      }

      assert(found);

      auto [lowest_tenant, lowest_page] = lowest_key;

      Node lowest_page_node = segtree_of_tenant_pages[lowest_tenant].node(lowest_page);
      lowest_page_node.active = false;
      segtree_of_tenant_pages[lowest_tenant].update(lowest_page, lowest_page_node);

      Node page_node = segtree_of_tenant_pages[tenant].node(page);
      page_node.active = true;
      page_node.last_access_time = ++access_timer;
      page_node.total_reference_count++;
      segtree_of_tenant_pages[tenant].update(page, page_node);

      tenant_current_buffer_size[lowest_tenant]--;
      tenant_current_buffer_size[tenant]++;

      int at_buffer_position = page_position_in_buffer[lowest_tenant][lowest_page];
      page_position_in_buffer[lowest_tenant][lowest_page] = 0;
      page_position_in_buffer[tenant][page] = at_buffer_position;
    }

    return make_pair(page_position_in_buffer[tenant][page], got_hit);
  }
};

namespace ReplacementAlgorithm {
  #define LRU_REF_INDEX 0
  #define LRU_INDEX 1
  #define LFU_INDEX 2
  #define MRU_INDEX 3

  bool LRU_REF_compare(const Node& node1, const Node& node2) {
    if (!node1.active) return false;
    if (!node2.active) return true;
    return node1.last_access_time < node2.last_access_time;
  }
  bool LRU_compare(const Node& node1, const Node& node2) {
    if (!node1.active) return false;
    if (!node2.active) return true;
    return node1.last_access_time < node2.last_access_time;
  }
  bool LFU_compare(const Node& node1, const Node& node2) {
    if (!node1.active) return false;
    if (!node2.active) return true;
    return make_pair(node1.total_reference_count, node1.last_access_time) < make_pair(node2.total_reference_count, node2.last_access_time);
  }
  bool MRU_compare(const Node& node1, const Node& node2) {
    if (!node1.active) return false;
    if (!node2.active) return true;
    return node1.last_access_time > node2.last_access_time;
  }

  vector<Comparator> algo_comparators;
  vector<bool> algo_uses_page_buffer_hit_counts;
  vector<AlgorithmTemplate> algorithms;
  AlgorithmTemplate *current_algorithm;
  int current_algorithm_index;

  // Detect and switch between LRU_REF, LRU, and LFU
  vector<int> window_hit_counts(3, 0);
  vector<int> window_fault_counts(3, 0);
  vector<deque<bool>> window_hit_fault_records(3);
  const int min_window_size_for_switch = 1e3;
  const vector<vector<int>> algo_resistance = {
    {1000, -200, -27},
    {-30, 1000, -30},
    {-30, -30, 1000}
  };
  int lru_switch_remaining = 1;
  int lfu_switch_remaining = 1;
  int max_lru_to_lru_ref_back_delay = 2e4;

  void update_trackers_for_lfruref_detection(int algo_index, bool got_hit) {
    if (algorithms[algo_index].buffer_positions_used >= total_buffer_size) {
      if (current_algorithm_index == LRU_INDEX) max_lru_to_lru_ref_back_delay--;

      if (got_hit) window_hit_counts[algo_index]++;
      else window_fault_counts[algo_index]++;
      window_hit_fault_records[algo_index].push_back(got_hit);

      if ((int)window_hit_fault_records[algo_index].size() > min_window_size_for_switch) {
        if (window_hit_fault_records[algo_index].front()) window_hit_counts[algo_index]--;
        else window_fault_counts[algo_index]--;
        window_hit_fault_records[algo_index].pop_front();
      }
    }
  }

  bool should_switch_to_lfruref(int algo_index) {
    if (algo_index == LRU_INDEX and !lru_switch_remaining) return false;
    if (algo_index == LFU_INDEX and !lfu_switch_remaining) return false;
    if (current_algorithm_index == LRU_INDEX and algo_index == LRU_REF_INDEX and max_lru_to_lru_ref_back_delay < 0) return false;

    int comparison_algo = current_algorithm_index;
    if (current_algorithm_index != LRU_REF_INDEX and algo_index != LRU_REF_INDEX and algo_index != current_algorithm_index) {
      comparison_algo = LRU_REF_INDEX;
    }

    return algorithms[algo_index].buffer_positions_used >= total_buffer_size and
      algorithms[comparison_algo].buffer_positions_used >= total_buffer_size and
      (int)window_hit_fault_records[algo_index].size() >= min_window_size_for_switch and
      window_hit_counts[algo_index] - window_fault_counts[algo_index] >= algo_resistance[algo_index][comparison_algo] + window_hit_counts[comparison_algo] - window_fault_counts[comparison_algo];
  }

  void switch_to_lfruref(int algo_index) {
    current_algorithm_index = algo_index;
    current_algorithm->update_comparator(algo_comparators[algo_index], algo_uses_page_buffer_hit_counts[algo_index]);

    for (int i = 0; i < 3; i++) {
      window_hit_counts[i] = 0;
      window_fault_counts[i] = 0;
      window_hit_fault_records[i] = deque<bool>();
    }
    
    if (algo_index == LRU_INDEX) lru_switch_remaining--;
    if (algo_index == LFU_INDEX) lfu_switch_remaining--;
  }   

  // Detect MRU from LFRU_REF
  const int max_hit_fault_records = 1000;
  vector<int> recent_hits(4, 0);
  vector<int> recent_faults(4, 0);
  vector<deque<bool>> recent_hit_fault_records(4);
  vector<map<pair<int, int>, bool>> keys_handled(4);
  const int mru_support = 300;
  int max_mru_delay = 3e4;
  int mru_switch_remaining = 1;

  void update_trackers_for_mru_detection(int algo_index, int got_hit, int tenant, int page) {
    if (algorithms[algo_index].buffer_positions_used >= total_buffer_size) {
      max_mru_delay -= mru_switch_remaining and algo_index == MRU_INDEX;
      if (keys_handled[algo_index].find(make_pair(tenant, page)) != keys_handled[algo_index].end()) {
        if (got_hit) recent_hits[algo_index]++;
        else recent_faults[algo_index]++;
        recent_hit_fault_records[algo_index].push_back(got_hit);

        if ((int)recent_hit_fault_records[algo_index].size() > max_hit_fault_records) {
          if (recent_hit_fault_records[algo_index].front()) recent_hits[algo_index]--;
          else recent_faults[algo_index]--;
          recent_hit_fault_records[algo_index].pop_front();
        }
      }
    }
    keys_handled[algo_index][make_pair(tenant, page)] = true;
  }

  bool should_switch_to_mru(vector<bool> got_hit) {
    return current_algorithm_index == LRU_REF_INDEX and
      mru_switch_remaining and
      lru_switch_remaining and
      lfu_switch_remaining and
      max_mru_delay >= 0 and
      !got_hit[LRU_REF_INDEX] and
      algorithms[LRU_REF_INDEX].buffer_positions_used >= total_buffer_size and
      (int)recent_hit_fault_records[LRU_REF_INDEX].size() >= max_hit_fault_records and
      recent_hits[LRU_REF_INDEX] - recent_faults[LRU_REF_INDEX] <= mru_support;
  }

  void switch_to_mru() {
    current_algorithm_index = MRU_INDEX;
    current_algorithm->update_comparator(algo_comparators[MRU_INDEX], algo_uses_page_buffer_hit_counts[MRU_INDEX]);

    for (int t = 1; t <= total_tenants; t++) {
      for (int page = 1; page <= db_sizes[t]; page++) {
        current_algorithm->page_buffer_hit_count[t][page] = 0;
        if (current_algorithm->page_real_access_time[t][page]) {
          Node node = current_algorithm->segtree_of_tenant_pages[t].node(page);
          node.last_access_time = current_algorithm->page_real_access_time[t][page];
          current_algorithm->segtree_of_tenant_pages[t].update(page, node);
        }
      }
    }

    for (int i = 0; i < 4; i++) {
      recent_hits[i] =  0;
      recent_faults[i] =  0;
      recent_hit_fault_records[i] = deque<bool>();
      keys_handled[i].clear();
    }

    mru_switch_remaining--;
  }

  int handle_operation(int tenant, int page) {
    vector<bool> got_hit(4, false);

    for (int algo_index = 0; algo_index < 4; algo_index++) {
      if (algo_index == MRU_INDEX and (!mru_switch_remaining or max_mru_delay <= 0)) continue;

      got_hit[algo_index] = algorithms[algo_index].handle_operation(tenant, page).second;
      if (algo_index < MRU_INDEX) update_trackers_for_lfruref_detection(algo_index, got_hit[algo_index]);
      update_trackers_for_mru_detection(algo_index, got_hit[algo_index], tenant, page);
    }

    if (current_algorithm_index != MRU_INDEX) {
      if (should_switch_to_mru(got_hit)) {
        switch_to_mru();
      }
      else {
        for (int algo_index = 0; algo_index < 3; algo_index++) {
          if (should_switch_to_lfruref(algo_index)) {
            switch_to_lfruref(algo_index);
            break;
          }
        }
      }
    }
      
    // else if (should_switch_from_mru(got_hit)) {
    //   assert(min_lru_delay <= 0);
    //   switch_from_mru();
    // }

    return current_algorithm->handle_operation(tenant, page).first;
  }

  void initialize() {
    algo_comparators.emplace_back(LRU_REF_compare);
    algo_uses_page_buffer_hit_counts.push_back(true);
    algo_comparators.emplace_back(LRU_compare);
    algo_uses_page_buffer_hit_counts.push_back(false);
    algo_comparators.emplace_back(LFU_compare);
    algo_uses_page_buffer_hit_counts.push_back(false);
    algo_comparators.emplace_back(MRU_compare);
    algo_uses_page_buffer_hit_counts.push_back(false);

    for (int i = 0; i < 4; i++) {
      algorithms.emplace_back(algo_comparators[i], algo_uses_page_buffer_hit_counts[i]);
    }

    current_algorithm_index = LRU_REF_INDEX;
    current_algorithm = new AlgorithmTemplate(algo_comparators[current_algorithm_index], algo_uses_page_buffer_hit_counts[current_algorithm_index]);
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
