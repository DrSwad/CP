#include <bits/stdc++.h>
using namespace std;

const int N = 5e3 + 5;
const int mod = 1e9 + 7;

int add(int a, int b) {
  int c = a + b;
  return c < mod ? c : c - mod;
}

int mul(int a, int b) {
  return 1ll * a * b % mod;
}

int C[N][N];
int dp[N][N];
int pref_dp[N][N];
int pref_dp2[N][N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  for (int n = 0; n < N; n++) {
    for (int k = 0; k < N; k++) {
      if (k == 0 or k == n) C[n][k] = 1;
      else if (0 < k and k < n) {
        C[n][k] = add(C[n - 1][k], C[n - 1][k - 1]);
      }
    }
  }

  for (int s = 1; s < N; s++) {
    for (int b = 1; b < N; b++) {
      if (b < s) dp[s][b] = 0;
      else if (s == 1) dp[s][b] = 1;
      else if (s == b) dp[s][b] = 1;
      else {
        dp[s][b] = add(mul(s, pref_dp[s][b - s]), mod - pref_dp2[s][b - s]);
      }

      pref_dp[s][b] = add(pref_dp[s - 1][b], dp[s][b]);
      pref_dp2[s][b] = add(pref_dp2[s - 1][b], mul(s - 1, dp[s][b]));
    }
  }

  int s, b;
  cin >> s >> b;
  cout << dp[s][b] << "\n";

  return 0;
}