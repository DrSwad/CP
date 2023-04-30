#include <bits/stdc++.h>
using namespace std;

const int MAX_TENANTS = 10;
const int MAX_BUFFER_SIZE = 1e6;
const int MAX_OPERATIONS = 1e6;
const int MAX_PRIORITY = 10;
const int MAX_DB_SIZE = 1e5;
const int MAX_TENANT_BUFFER_SIZE = 1e5;

int total_tenants;
int total_buffer_size;
int total_operations;

int priorities[MAX_TENANTS + 1];
int db_sizes[MAX_TENANTS + 1];

int buffer_min_sizes[MAX_TENANTS + 1];
int buffer_base_sizes[MAX_TENANTS + 1];
int buffer_max_sizes[MAX_TENANTS + 1];

struct Node {
  int tenant_id = 0;
  int page_id = 0;
  bool active = false;
  int first_access_time = 0;
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
  SegmentTree(int _n, int t) {
    n = _n;
    a.emplace_back();
    for (int i = 1; i <= n; i++) {
      a.emplace_back();
      a.back().tenant_id = t;
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
    segtree_of_tenant_pages.emplace_back(1, 0);
    for (int t = 1; t <= total_tenants; t++) {
      segtree_of_tenant_pages.emplace_back(db_sizes[t], t);
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
      page_node.first_access_time = ++access_timer;
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
      page_node.first_access_time = ++access_timer;
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
      page_node.first_access_time = ++access_timer;
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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int> uid(0, 1e9);
auto gen = bind(uid, rng);

namespace ReplacementAlgorithm {
  vector<Comparator> algo_comparators;
  vector<bool> algo_uses_page_buffer_hit_counts;
  vector<AlgorithmTemplate> algorithms;
  AlgorithmTemplate *current_algorithm;
  int current_algorithm_index;
  int operations_processed = 0;

  #define LRU_REF_INDEX 0
  #define LRU_INDEX 1
  #define LFU_INDEX 2
  #define MRU_INDEX 3
  #define CUSTOM_INDEX 4

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
  bool Custom_compare(const Node& node1, const Node& node2) {
    if (!node1.active) return false;
    if (!node2.active) return true;
    return node1.last_access_time < node2.last_access_time; 
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
    algo_comparators.emplace_back(Custom_compare);
    algo_uses_page_buffer_hit_counts.push_back(false);

    for (int i = 0; i < 5; i++) {
      algorithms.emplace_back(algo_comparators[i], algo_uses_page_buffer_hit_counts[i]);
    }

    current_algorithm_index = LRU_INDEX;
    current_algorithm = new AlgorithmTemplate(algo_comparators[current_algorithm_index], algo_uses_page_buffer_hit_counts[current_algorithm_index]);
  }

  int handle_operation(int tenant, int page) {
    ++operations_processed;

    function<bool(const Node&, const Node&)> comparator = [&](const Node &node1, const Node &node2) {
      return make_pair(buffer_base_sizes[node1.tenant_id] - current_algorithm->tenant_current_buffer_size[node1.tenant_id], node1.last_access_time) < make_pair(buffer_base_sizes[node2.tenant_id] - current_algorithm->tenant_current_buffer_size[node2.tenant_id], node2.last_access_time);
    };
    current_algorithm->compare = comparator;

    return current_algorithm->handle_operation(tenant, page).first;
  }
}

int main() {
  cin >> total_tenants;
  cin >> total_buffer_size;
  cin >> total_operations;

  for (int t = 1; t <= total_tenants; t++) {
    cin >> priorities[t];
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
