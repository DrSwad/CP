#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector c(n, 0);
  for (int &i : c) cin >> i, i--;

  vector adj(n, vector<int>());

  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  vector sz(n, 0);

  function<void(int, int)> dfs =
    [&](int at, int from) {
      sz[at] = 1;
      for (int to : adj[at]) {
        if (to != from) {
          dfs(to, at);
          sz[at] += sz[to];
        }
      }
    };

  dfs(0, -1);

  vector freq(n, 0);
  map<int, long long> color_sum;
  vector subtree(n, vector<int>());
  vector ans(n, 0ll);

  function<void(int)> include =
    [&](int color) {
      color_sum[freq[color]] -= (color + 1);
      if (color_sum[freq[color]] == 0) {
        color_sum.erase(freq[color]);
      }
      freq[color]++;
      color_sum[freq[color]] += (color + 1);
    };

  function<void(int)> remove =
    [&](int color) {
      color_sum[freq[color]] -= (color + 1);
      if (color_sum[freq[color]] == 0) {
        color_sum.erase(freq[color]);
      }
      freq[color]--;
      color_sum[freq[color]] += (color + 1);
    };

  function<void(int, int)> dsu =
    [&](int at, int from) {
      int largest_child = -1;

      for (int to : adj[at]) {
        if (to != from) {
          if (largest_child == -1 or sz[to] > sz[largest_child]) {
            largest_child = to;
          }
        }
      }

      for (int to : adj[at]) {
        if (to != from and to != largest_child) {
          dsu(to, at);
          for (int color : subtree[to]) {
            remove(color);
          }
        }
      }

      if (largest_child != -1) {
        dsu(largest_child, at);
        swap(subtree[at], subtree[largest_child]);
      }

      for (int to : adj[at]) {
        if (to != from and to != largest_child) {
          while (!subtree[to].empty()) {
            int color = subtree[to].back();
            subtree[to].pop_back();
            include(color);
            subtree[at].push_back(color);
          }
        }
      }

      subtree[at].push_back(c[at]);
      include(c[at]);

      ans[at] = color_sum.rbegin()->second;
    };

  dsu(0, -1);

  for (int i = 0; i < n; i++) {
    if (i) cout << " ";
    cout << ans[i];
  }
  cout << "\n";

  return 0;
}