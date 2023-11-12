#include <bits/stdc++.h>
using namespace std;

const int mod = int(1e9) + 9;

int add(int a, int b) {
  int c = a + b;
  return c < mod ? c : c - mod;
}

int mul(int a, int b) {
  return 1ll * a * b % mod;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<vector<pair<int, int>>> adj(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    u--, v--;
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
  }

  vector<int> fact(n + 1), inv(n + 1), ifact(n + 1);
  inv[1] = fact[0] = ifact[0] = 1;
  for (int i = 2; i <= n; i++) inv[i] = mul(inv[mod % i], mod - mod / i);
  for (int i = 1; i <= n; i++) fact[i] = mul(fact[i - 1], i);
  for (int i = 1; i <= n; i++) ifact[i] = mul(ifact[i - 1], inv[i]);

  int ans = 0;

  function<void(int, int, int, int, int)> dfs =
    [&](int at, int from, int root, int dist, int tot_w) {
      if (at > root) {
        ans = add(ans, mul(tot_w, mul(fact[n], mul(inv[dist + 1], 2))));
      }

      for (auto [to, w] : adj[at]) {
        if (to != from) {
          dfs(to, at, root, dist + 1, add(tot_w, w));
        }
      }
    };

  for (int i = 0; i < n; i++) {
    dfs(i, -1, i, 0, 0);
  }

  cout << ans << "\n";

  return 0;
}