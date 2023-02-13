#include <bits/stdc++.h>
using namespace std;

const int N = 100 + 2; // CHANGE THIS
const int K = N * (N + 1) / 2;

int dp[N][K];

void init() {
  memset(dp, -1, sizeof dp);
  dp[0][0] = 0;

  for (int n = 1; n < N; n++) {
    for (int k = 1; k < K; k++) {
      for (int s = 1; s <= n and s * (s + 1) / 2 <= k; s++) {
        int nk = k - s * (s + 1) / 2;
        if (dp[n - s][nk] != -1) {
          dp[n][k] = s;
          continue;
        }
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  init();

  int t;
  cin >> t;

  while (t--) {
    int n, k;
    cin >> n >> k;
    // debug(n, k);

    if (k >= K or n % 2 == 1 or dp[n / 2][k] == -1) {
      cout << "impossible\n";
      continue;
    }

    n /= 2;
    string ans;
    int ends = 0;

    while (n) {
      // debug(n, k, dp[n][k]);
      assert(n >= 0);
      int cnt = dp[n][k];
      for (int i = 0; i < cnt - 1; i++) {
        ans += "()";
      }
      ans += "(";
      ends++;
      k -= cnt * (cnt + 1) / 2;
      n -= cnt;
    }

    while (ends--) {
      ans += ")";
    }

    assert(k == 0);
    cout << ans << "\n";
  }

  return 0;
}