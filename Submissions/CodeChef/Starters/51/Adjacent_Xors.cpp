#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n;
  ll x;
  cin >> n >> x;

  vector<ll> a(n);
  for (ll &i : a) cin >> i;

  vector<vector<ll>> dp(n, vector<ll>(2, 0));
  for (int i = 1; i < n; i++) {
    ll val[2] = {a[i - 1], a[i - 1] + x};

    for (int it = 0; it < 2; it++) {
      dp[i][it] = max(dp[i][it], (a[i] ^ val[0]) + dp[i - 1][0]);
      dp[i][it] = max(dp[i][it], (a[i] ^ val[1]) + dp[i - 1][1]);

      a[i] += x;
      x = -x;
    }
  }

  cout << max(dp[n - 1][0], dp[n - 1][1]) << "\n";
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