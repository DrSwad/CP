#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n, m;
  cin >> n >> m;

  vector<vector<ll>> v(n, vector<ll>(m));
  for (auto &row : v) {
    for (ll &i : row) cin >> i;
  }

  vector<ll> dp1(m, 0), dp2(m, 0);
  for (int i = 0; i < n; i++) {
    ll row_sum = 0;
    for (ll j : v[i]) row_sum += j;
    for (int j = 0; j < m; j++) {
      dp1[j] = max(dp1[j], dp1[j] + (row_sum - v[i][j] * m));
      dp2[j] = max(dp2[j], dp2[j] + (v[i][j] * m - row_sum));
    }
  }

  ll ans = 0;
  for (ll i : dp1) ans = max(ans, i);
  for (ll i : dp2) ans = max(ans, i);

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