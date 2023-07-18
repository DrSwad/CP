#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll solve(ll n, vector<vector<int>> v) {
  vector<ll> dp(n + 1);
  iota(dp.begin(), dp.end(), 0);
  for (int nn = 1; nn <= n; nn++) {
    for (int it = 0; it < 3; it++) {
      if (v[0][it] <= nn) {
        dp[nn] = max(dp[nn], dp[nn - v[0][it]] + v[1][it]);
      }
    }
  }
  return dp[n];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ll n;
  vector v(2, vector(3, 0));

  cin >> n;
  for (int it = 0; it < 2; it++) {
    for (int i = 0; i < 3; i++) {
      cin >> v[it][i];
    }
  }

  n = solve(n, v);
  swap(v[0], v[1]);
  n = solve(n, v);

  cout << n << "\n";

  return 0;
}