#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<vector<int>> adj(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  function<bool(int, int, int, int, int)> dfs =
    [&](int at, int from, int closest, int xr, int mask) {
      if (mask >> at & 1) {
        if (closest <= xr) return false;
        closest = 0;
        xr ^= a[at];
      }
      closest++;

      for (int to : adj[at]) {
        if (to != from) {
          if (!dfs(to, at, closest, xr, mask)) return false;
        }
      }

      return true;
    };

  int ans = 0;
  for (int mask = 0; mask < 1 << n; mask++) {
    if (dfs(0, -1, INT_MAX, 0, mask)) {
      int sum = 0;
      for (int i = 0; i < n; i++) {
        if (mask >> i & 1) sum += a[i];
      }
      ans = max(ans, sum);
    }
  }

  cout << ans << "\n";

  return 0;
}