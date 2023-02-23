#include <bits/stdc++.h>
using namespace std;

const int V = 10000;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<vector<int>> e(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    e[u].push_back(v);
    e[v].push_back(u);
  }

  vector<int> primes;
  {
    vector<bool> vis(V + 1, false);
    for (int p = 2; p <= V; p++) {
      if (!vis[p]) {
        primes.push_back(p);
        for (int q = 2 * p; q <= V; q += p) {
          vis[q] = true;
        }
      }
    }
  }

  vector<vector<int>> dp(n, vector<int>(V + 1));

  function<void(int, int)> dfs = [&](int at, int from) {
    for (int to : e[at]) {
      if (to != from) {
        dfs(to, at);
      }
    }

    for (int v = 2; v <= V; v++) {
      dp[at][v] = a[at] == v ? 0 : v;
      for (int to : e[at]) {
        if (to != from) {
          dp[at][v] += dp[to][v];
        }
      }
    }

    vector<int> ndp(V + 1, INT_MAX);
    for (int p : primes) {
      int mn = INT_MAX;
      for (int q = p; q <= V; q += p) {
        mn = min(mn, dp[at][q]);
      }
      for (int q = p; q <= V; q += p) {
        ndp[q] = min(ndp[q], mn);
      }
    }

    dp[at] = ndp;
  };

  dfs(0, -1);

  cout << *min_element(dp[0].begin() + 2, dp[0].end()) << "\n";

  return 0;
}