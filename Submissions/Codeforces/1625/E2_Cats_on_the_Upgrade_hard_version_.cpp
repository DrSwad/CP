#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag,
  tree_order_statistics_node_update>
  ordered_set;

template<typename T, class F = function<T(const T&, const T&)>>
class SegmentTree {
  int n;
  vector<T> a;
  vector<T> st;
  T st_default;
  F merge;
  F setval;
  void build(int stI, int L, int R) {
    if (L == R) {
      st[stI] = a[L - 1];
      return;
    }

    int mid = (L + R) >> 1;
    build(stI << 1, L, mid);
    build(stI << 1 | 1, mid + 1, R);

    st[stI] = merge(st[stI << 1], st[stI << 1 | 1]);
  }
  void update(int stI, int L, int R, int at, T val) {
    if (L == R) {
      st[stI] = setval(st[stI], val);
      return;
    }

    int mid = (L + R) >> 1;
    if (at <= mid) update(stI << 1, L, mid, at, val);
    else update(stI << 1 | 1, mid + 1, R, at, val);

    st[stI] = merge(st[(stI << 1)], st[(stI << 1) + 1]);
  }
  T query(int stI, int L, int R, int l, int r) {
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
  SegmentTree(const vector<T> &_a, const F &_merge, const F &_setval, T st_default, bool build_init) {
    n = static_cast<int>(_a.size());
    a = _a;
    st.resize(4 * n + 1, st_default);
    this->st_default = st_default;
    merge = _merge;
    setval = _setval;
    if (build_init) build(1, 1, n);
  }
  T query(int l, int r) { // range [l, r], 1-based index
    if (r < 1 || n < l || r < l) return st_default;
    l = max(l, 1); r = min(r, n);
    return query(1, 1, n, l, r);
  }
  void update(int at, T val) { // at is 1-based index
    if (at < 1 || n < at) return;
    update(1, 1, n, at, val);
  }
};

void test_case() {
  int n, q;
  cin >> n >> q;

  string s;
  cin >> s;

  vector<vector<pair<int, int>>> chains;
  int total_chains = 0;
  vector<int> chain_ids(n);

  for (int i = n - 1; i >= 0; i--) {
    if (s[i] == ')') chain_ids[i] = -1;
    else if (i + 1 >= n) chain_ids[i] = -1;
    else if (s[i + 1] != ')' and chain_ids[i + 1] == -1) chain_ids[i] = -1;
    else {
      int j;
      if (s[i + 1] == ')') j = i + 1;
      else j = chains[chain_ids[i + 1]][0].second + 1;

      if (j >= n or s[j] != ')') chain_ids[i] = -1;
      else {
        int chain_id;
        if (j + 1 >= n or chain_ids[j + 1] == -1) {
          chains.push_back({});
          chain_id = total_chains;
          total_chains++;
        }
        else chain_id = chain_ids[j + 1];
        chain_ids[i] = chain_id;
        chains[chain_id].push_back({i, j});
      }
    }
  }

  for (auto &chain : chains) {
    reverse(chain.begin(), chain.end());
  }

  vector<int> chain_lengths(total_chains);
  vector<long long> chain_head_contrib(n, 0);
  vector<ordered_set> chain_elems(total_chains);

  for (int chain_id = 0; chain_id < total_chains; chain_id++) {
    int chain_length = chain_lengths[chain_id] = chains[chain_id].size();
    int chain_head = chains[chain_id][0].first;
    chain_head_contrib[chain_head] = (long long)chain_length * (chain_length + 1) / 2;
    for (auto [st, en] : chains[chain_id]) {
      chain_elems[chain_id].insert(st);
    }
  }

  // debug(chains);
  // debug(chain_ids);
  // debug(chain_lengths);
  // debug(chain_head_contrib);
  // debug(chain_elems);

  SegmentTree<long long> st(chain_head_contrib, [&](long long i, long long j) {return i + j;}, [&](long long i, long long j) {return i + j;}, 0ll, true);

  while (q--) {
    int t, l, r;
    cin >> t >> l >> r;
    l--, r--;
    // debug(t, l, r);

    int chain_id = chain_ids[l];
    assert(chain_id != -1);

    if (t == 1) {
      int chain_head = chains[chain_id][0].first;
      st.update(chain_head + 1, -chain_lengths[chain_id]);
      chain_lengths[chain_id]--;
      chain_elems[chain_id].erase(l);
    }
    else {
      long long ans = st.query((l + 1) + 1, (r + 1));
      int len = chain_elems[chain_id].order_of_key(r) - chain_elems[chain_id].order_of_key(l);
      ans += (long long)len * (len + 1) / 2;
      cout << ans << "\n";
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  // cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}