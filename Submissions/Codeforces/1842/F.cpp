#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector adj(n, vector<int>());

  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  vector ans(n + 1, 0);
  vector<int> depth_freq(n + 1, 0);

  function<void(int, int, int depth)> dfs =
    [&](int at, int from, int depth) {
      depth_freq[depth]++;
      for (int to : adj[at]) {
        if (to != from) {
          dfs(to, at, depth + 1);
        }
      }
    };

  for (int i = 0; i < n; i++) {
    dfs(i, -1, 0);

    int depth = 0;
    int sum = 0;

    for (int k = 0; k <= n; k++) {
      ans[k] = max(ans[k], (n - 1) * k - 2 * sum);
      if (k < n) {
        while (depth_freq[depth] == 0) depth++;
        sum += depth;
        depth_freq[depth]--;
      }
    }
  }

  for (int k = 0; k <= n; k++) {
    if (k) cout << " ";
    cout << ans[k];
  }
  cout << "\n";

  return 0;
}