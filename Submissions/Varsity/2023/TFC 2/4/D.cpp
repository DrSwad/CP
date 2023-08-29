#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int B = 1e4 + 5;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  vector<ll> dp(B);
  dp[1] = 0;
  dp[0] = 0;
  for (int b = 2; b < B; b++) {
    dp[b] = dp[b - 2] + (b - 2) / 2;
  }

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    int b;
    cin >> b;
    cout << dp[b] << "\n";
  }

  return 0;
}