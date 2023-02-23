#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<vector<int>> e(n);
  vector<int> d(n, 0);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    e[u].push_back(v);
    e[v].push_back(u);
    d[u]++, d[v]++;
  }

  int tot_heavy = 0;
  for (int i = 0; i < n; i++) {
    tot_heavy += d[i] >= 3;
  }

  bool ans = true;

  function<int(int, int)> dfs = [&](int at, int from) {
    int heavy_branch = 0;
    int curr_heavy = d[at] >= 3;
    for (int to : e[at]) {
      if (to != from) {
        int got = dfs(to, at);
        if (got > 0) heavy_branch++;
        curr_heavy += got;
      }
    }
    heavy_branch += curr_heavy < tot_heavy;
    if (d[at] >= 3 and heavy_branch > 2) ans = false;
    return curr_heavy;
  };

  dfs(0, -1);

  cout << (ans ? "YES\n" : "NO\n");

  return 0;
}