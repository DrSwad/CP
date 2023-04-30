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

class SegmentTreeLazy {
private:
  int n;
  vector<double> a;
  vector<bool> alive;
  vector<int> st;
  vector<double> lz;

  double min_score_for_page;
  double max_score_for_page;

  inline void push(int stI, int L, int R) {
    if (L == R) {
      if (alive[L - 1]) {
        a[L - 1] += lz[stI];
        a[L - 1] = max(a[L - 1], min_score_for_page);
        a[L - 1] = min(a[L - 1], max_score_for_page);
      }
    }
    else {
      lz[stI << 1] += lz[stI];
      lz[stI << 1 | 1] += lz[stI];
    }
    lz[stI] = 0;
  }

  int merge(int stL, int stR) {
    if (stL == 0) return stR;
    else if (stR == 0) return stL;
    else if (a[stL - 1] <= a[stR - 1]) return stL;
    else return stR;
  }

  void add(int stI, int L, int R, int l, int r, double val) {
    if (lz[stI] != 0) push(stI, L, R);
    if (r < L or R < l) return;
    if (l <= L && R <= r) {
      lz[stI] += val;
      return push(stI, L, R);
    }
    int mid = (L + R) >> 1;
    add(stI << 1, L, mid, l, r, val);
    add(stI << 1 | 1, mid + 1, R, l, r, val);
    st[stI] = merge(st[stI << 1], st[stI << 1 | 1]);
  }

  double query(int stI, int L, int R, int l, int r) {
    if (r < L or R < l) return 0;
    if (lz[stI] != 0) push(stI, L, R);
    if (l <= L && R <= r) return st[stI];
    int mid = (L + R) >> 1;
    return merge(
      query(stI << 1, L, mid, l, r),
      query(stI << 1 | 1, mid + 1, R, l, r)
      );
  }

  void set_life_state(int stI, int L, int R, int at, bool state) {
    if (lz[stI] != 0) push(stI, L, R);
    if (at < L or R < at) return;
    if (at <= L && R <= at) {
      push(stI, L, R);
      alive[at - 1] = state;
      st[stI] = alive[at - 1] ? at : 0;
      return;
    }
    int mid = (L + R) >> 1;
    set_life_state(stI << 1, L, mid, at, state);
    set_life_state(stI << 1 | 1, mid + 1, R, at, state);
    st[stI] = merge(st[stI << 1], st[stI << 1 | 1]);
  }

public:
  SegmentTreeLazy(int n, double min_score_for_page, double max_score_for_page) {
    this->n = n;
    this->a.resize(n, 0);
    st.resize(4 * n + 1, 0);
    lz.resize(4 * n + 1, 0);
    alive.resize(4 * n + 1, 0);

    this->min_score_for_page = min_score_for_page;
    this->max_score_for_page = max_score_for_page;
  }
  int query(int l, int r) { // range [l, r], 1-based index
    if (r < 1 || n < l || r < l) return 0;
    l = max(l, 1); r = min(r, n);
    return query(1, 1, n, l, r);
  }
  void add(int l, int r, double val) { // range [l, r], 1-based index
    if (r < 1 || n < l || r < l) return;
    l = max(l, 1); r = min(r, n);
    add(1, 1, n, l, r, val);
  }
  void set_life_state(int at, bool state) { // at 1-based index
    if (at < 1 || at > n) return;
    set_life_state(1, 1, n, at, state);
  }
  double get_page_score(int at) { // at 1-based index
    assert(1 <= at || at <= n);
    assert(alive[at - 1]);
    return a[query(at, at) - 1];
  }
};

namespace ReplacementAlgorithm {
  int tenant_current_buffer_size[MAX_TENANTS + 1];
  vector<SegmentTreeLazy> st_of_tenant_pages;

  int buffer_positions_used = 0;
  int page_position_in_buffer[MAX_TENANTS + 1][MAX_DB_SIZE + 1];

  double score_for_buffer_hit;
  double score_for_non_buffer_hit;
  double score_for_buffer_fault;
  const double min_score_for_page = -2;
  const double max_score_for_page = 20;

  void initialize() {
    st_of_tenant_pages.emplace_back(0, min_score_for_page, max_score_for_page);
    for (int t = 1; t <= total_tenants; t++) {
      st_of_tenant_pages.emplace_back(db_sizes[t], min_score_for_page, max_score_for_page);
    }

    score_for_buffer_hit = 1.5;
    score_for_non_buffer_hit = 1;
    score_for_buffer_fault = - (double)1 / total_buffer_size;
  }

  int get_least_scoring_page(int tenant) {
    return st_of_tenant_pages[tenant].query(1, db_sizes[tenant]);
  }

  void add_score_to_tenant_all_pages(int tenant, double score) {
    st_of_tenant_pages[tenant].add(1, db_sizes[tenant], score);
  }

  void add_score_to_page(int tenant, int page, double score) {
    st_of_tenant_pages[tenant].add(page, page, score);
  }

  double get_page_score(int tenant, int page) {
    return st_of_tenant_pages[tenant].get_page_score(page);
  }

  void set_page_life_state(int tenant, int page, bool state) {
    st_of_tenant_pages[tenant].set_life_state(page, state);
    if (state) {
      double prv_score = st_of_tenant_pages[tenant].get_page_score(page);
      st_of_tenant_pages[tenant].set_life_state(page, -prv_score / 2);
    }
  }

  int handle_operation(int tenant, int page) {
    for (int t = 1; t <= total_tenants; t++) {
      add_score_to_tenant_all_pages(t, score_for_buffer_fault);
    }

    if (page_position_in_buffer[tenant][page] != 0) {
      // cerr << "Page already exists" << endl;
      
      add_score_to_page(tenant, page, - score_for_buffer_fault + score_for_buffer_hit);
    }
    else if (tenant_current_buffer_size[tenant] >= buffer_max_sizes[tenant]) {
      // cerr << "Page must replace own tenant's page" << endl;
      
      int least_scoring_page = get_least_scoring_page(tenant);
      assert(least_scoring_page != 0);

      set_page_life_state(tenant, least_scoring_page, false);
      set_page_life_state(tenant, page, true);
      add_score_to_page(tenant, page, score_for_non_buffer_hit);

      int at_buffer_position = page_position_in_buffer[tenant][least_scoring_page];
      page_position_in_buffer[tenant][least_scoring_page] = 0;
      page_position_in_buffer[tenant][page] = at_buffer_position;
    }
    else if (buffer_positions_used < total_buffer_size) {
      // cerr << "Empty buffer available" << endl;

      set_page_life_state(tenant, page, true);
      add_score_to_page(tenant, page, score_for_buffer_hit);

      tenant_current_buffer_size[tenant]++;

      buffer_positions_used++;     
      page_position_in_buffer[tenant][page] = buffer_positions_used;
    }
    else {
      // cerr << "Replace least_scoring_page" << endl;

      double least_score = HUGE_VAL;
      bool found = false;
      pair<int, int> least_scoring_key;

      for (int t = 1; t <= total_tenants; t++) {
        if (tenant_current_buffer_size[t] <= buffer_min_sizes[t] - (t == tenant)) {
          continue;
        }

        int cur_least_scoring_page = get_least_scoring_page(t);
        assert(cur_least_scoring_page != 0);
        if (!found) found = true;

        double cur_least_score = get_page_score(t, cur_least_scoring_page);
        if (cur_least_score < least_score) {
          least_score = cur_least_score;
          least_scoring_key = make_pair(t, cur_least_scoring_page);
        }
      }

      assert(found);

      auto [least_scoring_tenant, least_scoring_page] = least_scoring_key;

      tenant_current_buffer_size[least_scoring_tenant]--;
      tenant_current_buffer_size[tenant]++;

      set_page_life_state(least_scoring_tenant, least_scoring_page, false);
      set_page_life_state(tenant, page, true);
      add_score_to_page(tenant, page, score_for_non_buffer_hit);

      int at_buffer_position = page_position_in_buffer[least_scoring_tenant][least_scoring_page];
      page_position_in_buffer[least_scoring_tenant][least_scoring_page] = 0;
      page_position_in_buffer[tenant][page] = at_buffer_position;
    }

    assert(page_position_in_buffer[tenant][page] != 0);
    return page_position_in_buffer[tenant][page];
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
