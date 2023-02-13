#include <bits/stdc++.h>
using namespace std;

void test_case() {
  string s;
  cin >> s;
  reverse(s.begin(), s.end());
  int n = s.length();
  s = " " + s;

  long long dp[n + 1][2][2] = {0};
  dp[0][0][0] = 1;

  for (int i = 1; i <= n; i++) {
    for (int c1 = 0; c1 < 2; c1++) {
      for (int c2 = 0; c2 < 2; c2++) {
        for (int d1 = 0; d1 < 10; d1++) {
          for (int d2 = 0; d2 < 10; d2++) {
            int sum = d1 + d2 + c1;
            int d3 = sum % 10;
            int c3 = sum / 10;

            if (d3 == s[i] - '0') {
              dp[i][c2][c3] += dp[i - 1][c1][c2];
            }
          }
        }
      }
    }
  }

  cout << dp[n][0][0] - 2 << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t;
  cin >> t;

  while (t--) {
    test_case();
  }

  return 0;
}