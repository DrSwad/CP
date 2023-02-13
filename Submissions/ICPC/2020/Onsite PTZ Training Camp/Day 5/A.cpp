#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e6 + 5;

ll dp[N];

void init() {
  for (int x = 1; x < N; x++) {
    for (int xy = 2 * x; xy < N; xy += x) {
      {
        int n = 2 * xy;
        if (n < N) {
          int z = xy;
          int y = xy - x;
          if (n % y == 0) {
            dp[n] = max(dp[n], 1ll * x * y * z);
          }
        }
      }

      {
        if (xy % 2 == 0) {
          int n = xy / 2 * 3;
          if (n < N) {
            int z = n / 3;
            int y = xy - x;
            if (n % y == 0) {
              dp[n] = max(dp[n], 1ll * x * y * z);
            }
          }
        }
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  memset(dp, -1, sizeof dp);
  init();

  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;
    cout << dp[n] << "\n";
  }

  return 0;
}