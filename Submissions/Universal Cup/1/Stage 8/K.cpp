#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int p[2];
  int n;
  cin >> p[0] >> p[1] >> n;

  int len[2];
  for (int it = 0; it < 2; it++) {
    if (gcd(p[0], p[1]) != 1) len[it] = -1;
    else {
      len[it] = 0;
      while (len[it] % p[0] != p[0] - 1) len[it] += p[1];
    }
    swap(p[0], p[1]);
  }

  vector dp(2, vector(n + 1, 0));
  for (int d = 1; d <= n; d++) {
    for (int it = 0; it < 2; it++) {
      if (len[it] == -1 or d < len[it] + 2) dp[it][d] = (d + p[0] - 1) / p[0] + (d - 1 + p[1] - 1) / p[1];
      else dp[it][d] = (len[it] + p[0] - 1) / p[0] + (len[it] - 1 + p[1] - 1) / p[1] + min(dp[0][d - len[it]], dp[1][d - len[it]]);
      swap(p[0], p[1]);
    }
  }

  int ans = 0;
  int at[2] = {p[0], p[1]};
  while (at[0] <= n or at[1] <= n) {
    if (at[0] == at[1]) {
      int d = n - (at[0] - 2);
      ans += min(dp[0][d], dp[1][d]);
      break;
    }
    else {
      ans++;
      if (at[0] < at[1]) at[0] += p[0];
      else at[1] += p[1];
    }
  }

  cout << ans << "\n";

  return 0;
}
