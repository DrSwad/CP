#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 1e18;

void test_case() {
  int n, m;
  cin >> n >> m;

  int s, t;
  cin >> s >> t;
  s--, t--;

  int c, d;
  cin >> c >> d;

  vector<vector<pair<int, int>>> e(n);
  while (m--) {
    int u, v, w;
    cin >> u >> v >> w;
    u--, v--;
    e[u].emplace_back(v, w);
    e[v].emplace_back(u, w);
  }

  vector<ll> rc(n, INF);
  for (int i = 0; i < n; i++) {
    for (auto [j, w] : e[i]) {
      rc[i] = min(rc[i], (ll)w);
    }
  }

  function<bool(int)> check = [&](int init) {
    vector<vector<ll>> dp(n, vector<ll>(init, INF));
    dp[s][init - 1] = 0;
    priority_queue<pair<ll, pair<int, int>>> pq;
    pq.push({0, {s, init - 1}});

    while (!pq.empty()) {
      auto [c0, at] = pq.top(); pq.pop();
      c0 = -c0;
      auto [i0, j0] = at;
      if (c0 > dp[i0][j0]) continue;
      for (auto [i1, w] : e[i0]) {
        if (j0) {
          int j1 = j0 - 1;
          ll c1 = c0 + w;
          if (c1 < dp[i1][j1]) {
            dp[i1][j1] = c1;
            pq.push({-c1, {i1, j1}});
          }
        }
        int j1 = init - 1;
        ll c1 = c0 + 2ll * d + w;
        if (c1 < dp[i1][j1]) {
          dp[i1][j1] = c1;
          pq.push({-c1, {i1, j1}});
        }
      }
      int j1 = init - 1;
      int i1 = i0;
      ll c1 = c0 + rc[i0] + d;
      if (c1 < dp[i1][j1]) {
        dp[i1][j1] = c1;
        pq.push({-c1, {i1, j1}});
      }
    }

    for (int j = init - 1; j >= 0; j--) {
      if (dp[t][j] <= c) return true;
    }
    return false;
  };

  int L = 0, R = n + 1;
  while (R - L > 1) {
    int mid = (L + R) / 2;
    if (check(mid)) R = mid;
    else L = mid;
  }

  if (R <= n) cout << R << "\n";
  else cout << "Impossible\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}