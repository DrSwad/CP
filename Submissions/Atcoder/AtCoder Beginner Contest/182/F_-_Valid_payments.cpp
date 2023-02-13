#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  ll x;
  cin >> x;

  vector<ll> a(n);
  for (ll &i : a) cin >> i;
  reverse(a.begin(), a.end());

  vector<ll> dx(n);
  for (int i = 0; i < n; i++) {
    dx[i] = x / a[i];
    x %= a[i];
  }

  vector<vector<ll>> dp(n, vector<ll>(2, 0));
  dp[0][0] = dp[0][1] = 1;

  for (int i = 1; i < n; i++) {
    ll q = a[i - 1] / a[i];
    for (int c = 0; c < 2; c++) {
      ll add = dx[i] + c;
      assert(add <= q);

      dp[i][c] = dp[i - 1][add == q];
      if (0 < add and add < q) dp[i][c] += dp[i - 1][1];
    }
  }

  cout << dp[n - 1][0] << "\n";

  return 0;
}