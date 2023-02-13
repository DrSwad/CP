#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

int add(int a, int b) {
  int c = a + b;
  return c < mod ? c : c - mod;
}

int mul(int a, int b) {
  return 1ll * a * b % mod;
}

void test_case() {
  int n;
  cin >> n;

  vector<vector<int>> adj(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  vector<int> depth(n);

  function<void(int, int)> dfs = [&](int at, int from) {
    depth[at] = 1;
    for (int to : adj[at]) {
      if (to != from) {
        dfs(to, at);
        depth[at] = max(depth[at], 1 + depth[to]);
      }
    }
  };

  dfs(0, -1);

  int p2 = 1;
  for (int i = 1; i <= n - 1; i++) {
    p2 = mul(p2, 2);
  }

  int ans = 0;
  for (int i = 0; i < n; i++) {
    ans = add(ans, mul(p2, depth[i]));
  }

  cout << ans << "\n";
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