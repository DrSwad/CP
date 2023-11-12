#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;

int add(int a, int b) {
  int c = a + b;
  return c < mod ? c : c - mod;
}

int mul(int a, int b) {
  return 1ll * a * b % mod;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  vector dp_first(n + 1, 0);
  vector dp_carry(n + 1, vector(k, 0));

  dp_carry[1][0] = k;
  dp_first[1] = dp_carry[1][k - 1];
  dp_carry[1][k - 1] = 0;

  for (int i = 2; i <= n; i++) {
    for (int carry = k - 1; carry >= 0; carry--) {
      dp_carry[i][carry] = dp_carry[i - 1][carry];
      if (carry + 1 < k) {
        dp_carry[i][carry] = add(dp_carry[i][carry], dp_carry[i][carry + 1]);
      }
    }
    for (int carry = 0; carry < k - 1; carry++) {
      dp_carry[i][carry + 1] = add(dp_carry[i][carry + 1], mul(k - carry - 1, dp_carry[i - 1][carry]));
    }
    dp_first[i] = dp_carry[i][k - 1];
    dp_carry[i][k - 1] = 0;
  }

  vector pk(n + 1, 0);
  pk[0] = 1;
  for (int i = 1; i <= n; i++) {
    pk[i] = mul(pk[i - 1], k);
  }

  vector dp(n + 1, 0);

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= i; j++) {
      dp[i] = add(dp[i], mul(dp_first[j], add(dp[i - j], pk[i - j])));
    }
  }

  cout << dp[n] << "\n";

  return 0;
}