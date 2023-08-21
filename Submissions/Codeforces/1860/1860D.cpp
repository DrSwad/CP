#include <bits/stdc++.h>
using namespace std;

const int N = 100;
const int MX = N * (N - 1) / 2;

short dp[N + 1][N + 1][2 * MX + 1];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string s;
  cin >> s;
  int n = s.length();

  int mx = n * (n - 1) / 2;

  fill(dp[0][0], dp[0][0] + sizeof(dp) / sizeof(dp[0][0][0]), n);
  dp[0][0][mx] = 0;

  for (int i = 1; i <= n; i++) {
    for (int cnt0 = 0; cnt0 <= n; cnt0++) {
      int cnt1 = i - cnt0;

      for (int c = 0; c < 2; c++) {
        int prv0 = cnt0 - (c == 0);
        int prv1 = cnt1 - (c == 1);
        if (prv0 < 0 or prv1 < 0) continue;

        for (int prv_diff = 0; prv_diff <= 2 * mx; prv_diff++) {
          int cur_diff = prv_diff;
          if (c == 0) cur_diff += prv1;
          if (c == 1) cur_diff -= prv0;
          if (cur_diff < 0 or cur_diff > 2 * mx) continue;

          dp[i][cnt0][cur_diff] = min(dp[i][cnt0][cur_diff], (short)(dp[i - 1][prv0][prv_diff] + (c != s[i - 1] - '0')));
        }
      }
    }
  }

  int cnt0 = count(s.begin(), s.end(), '0');
  cout << dp[n][cnt0][mx] / 2 << "\n";

  return 0;
}