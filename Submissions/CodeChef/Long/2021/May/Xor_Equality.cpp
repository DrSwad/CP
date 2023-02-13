#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int N = 1e5 + 5;

int dp[N];

int main() {
  dp[1] = 1;
  for (int i = 2; i < N; i++) {
    dp[i] = dp[i - 1] * 2 % MOD;
  }

  int t;
  cin >> t;

  while (t--) {
    int n;
    scanf("%d", &n);
    printf("%d\n", dp[n]);
  }

  return 0;
}