#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, q;
  cin >> n >> q;

  int a, b;
  cin >> a >> b;

  vector<int> c(n);
  for (int &i : c) cin >> i;

  vector<vector<int>> adj(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  int ans;
  function<bool(int, int, int, int, int)> dfs =
    [&](int at, int from, int dest, int type, int w) {
      if (at == dest) {
        if (type == 1) {
          c[at] += w;
          return true;
        }
        else {
          ans += a * c[at] + b >= 0;
          return true;
        }
      }

      bool on_path = false;
      for (int to : adj[at]) {
        if (to != from) {
          if (dfs(to, at, dest, type, w)) {
            on_path = true;
            if (type == 1) {
              c[at] += w;
              return true;
            }
            else {
              ans += a * c[at] + b >= 0;
              return true;
            }
          }
        }
      }

      return on_path;
    };

  while (q--) {
    int type;
    cin >> type;

    if (type == 1) {
      int u, v, w;
      cin >> u >> v >> w;
      u--, v--;
      dfs(u, -1, v, type, w);
    }
    else {
      int u, v;
      cin >> u >> v;
      u--, v--;
      ans = 0;
      dfs(u, -1, v, type, 0);
      cout << ans << "\n";
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}