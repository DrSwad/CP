#include <bits/stdc++.h>
using namespace std;

const int BIG = 1e9;

// Returns number of unique elements
template<typename T>
int compress(vector<T> &a) {
  int n = a.size();
  vector<pair<T, int>> pairs(n);
  for (int i = 0; i < n; ++i) {
    pairs[i] = {a[i], i};
  }
  sort(pairs.begin(), pairs.end());
  int nxt = 0;
  for (int i = 0; i < n; ++i) {
    if (i > 0 && pairs[i - 1].first != pairs[i].first) nxt++;
    a[pairs[i].second] = nxt;
  }
  return n == 0 ? 0 : nxt + 1;
}

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  int q;
  cin >> q;

  vector<int> edges(q << 1);
  for (auto &i : edges) cin >> i;

  vector<int> qv = edges;
  sort(qv.begin(), qv.end());
  qv.resize(unique(qv.begin(), qv.end()) - qv.begin());

  int v = compress(edges);
  assert(v == qv.size());
  vector<vector<int>> out_adj(v), in_adj(v);
  for (int i = 0; i < q; i++) {
    int from = edges[i << 1], to = edges[i << 1 | 1];
    out_adj[from].push_back(to);
    in_adj[to].push_back(from);
  }

  for (int i = 0; i < v; i++) {
    sort(out_adj[i].begin(), out_adj[i].end());
    out_adj[i].resize(unique(out_adj[i].begin(), out_adj[i].end()) - out_adj[i].begin());
    sort(in_adj[i].begin(), in_adj[i].end());
    in_adj[i].resize(unique(in_adj[i].begin(), in_adj[i].end()) - in_adj[i].begin());
  }

  vector<bool> is_big(v);
  for (int i = 0; i < v; i++) {
    is_big[i] = out_adj[i].size() >= BIG;
  }

  for (int i = 0; i < v; i++) {
    vector<int> tmp = in_adj[i];
    in_adj[i].clear();
    for (int j : tmp) {
      if (is_big[j]) {
        in_adj[i].push_back(j);
      }
    }
  }

  vector<int> dp(v, 0), dp_big(v, 1), nxt(n, n), nxt_big(v, n), last_at(v, n);
  int ans = 0, ans_from = n;

  for (int i = n - 1; i >= 0; i--) {
    if (!binary_search(qv.begin(), qv.end(), a[i])) continue;
    int at = lower_bound(qv.begin(), qv.end(), a[i]) - qv.begin();

    int new_dp = 1;
    if (!is_big[at]) {
      for (int to : out_adj[at]) {
        if (dp[to] + 1 >= new_dp) {
          new_dp = dp[to] + 1;
          nxt[i] = last_at[to];
        }
      }
    }
    else {
      new_dp = dp_big[at];
      nxt[i] = nxt_big[at];
    }
    dp[at] = new_dp;

    if (dp[at] >= ans) {
      ans = dp[at];
      ans_from = i;
    }
    last_at[at] = i;

    for (int from : in_adj[at]) {
      assert(is_big[from]);
      if (dp[at] + 1 >= dp[from]) {
        dp_big[from] = dp[at] + 1;
        nxt_big[from] = i;
      }
    }
  }

  // assert(ans >= 2);
  cout << ans << "\n";

  for (int at = ans_from, prv; at < n; at = nxt[at]) {
    // if (at != ans_from) cout << " ";
    // cout << at + 1;
    assert(binary_search(qv.begin(), qv.end(), a[at]));
    int vat = lower_bound(qv.begin(), qv.end(), a[at]) - qv.begin();
    if (at != ans_from) {
      assert(binary_search(out_adj[prv].begin(), out_adj[prv].end(), vat));
    }
    prv = vat;
  }
  // cout << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}