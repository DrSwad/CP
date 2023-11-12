#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int mod = 998244353;

int add(int a, int b) {
  int c = a + b;
  return c < mod ? c : c - mod;
}

int mul(int a, int b) {
  return 1ll * a * b % mod;
}

ll binExp(ll a, ll e) {
  ll ret = 1;
  while (e) {
    if (e & 1) ret = mul(ret, a);
    a = mul(a, a), e >>= 1;
  }
  return ret;
}

void test_case() {
  int n, m;
  cin >> n >> m;

  vector<vector<int>> adj(n + 1);
  for (int i = 2; i <= n; i++) {
    int j = i / 2;
    adj[i].push_back(j);
    adj[j].push_back(i);
  }

  vector<int> dist_freq(n, 0);
  function<void(int, int, int, int)> dfs =
    [&](int at, int from, int root, int depth) {
      if (at >= root) dist_freq[depth]++;
      for (int to : adj[at]) {
        if (to != from) {
          dfs(to, at, root, depth + 1);
        }
      }
    };
  for (int i = 1; i <= n; i++) dfs(i, 0, i, 0);

  vector ways(n, vector(m + 1, 0));
  for (int d = 0; d < n; d++) {
    for (int mx = 1; mx <= m; mx++) {
      ways[d][mx] = add(binExp(mx, d + 1), mod - binExp(mx - 1, d + 1));
    }
  }

  // ans = sum(dist_freq[d] * ways[d][mx] * m**(n-(d+1)) * mx)
  int ans = 0;
  for (int d = 0; d < n; d++) {
    for (int mx = 1; mx <= m; mx++) {
      ans = add(ans, mul(dist_freq[d], mul(ways[d][mx], mul(binExp(m, n - (d + 1)), mx))));
    }
  }

  cout << ans << "\n";
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