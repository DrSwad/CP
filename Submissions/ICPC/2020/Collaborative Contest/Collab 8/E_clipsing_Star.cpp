#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
const int N = 1e6 + 5;

int n;
int a[N];
ld dp[N][2];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) scanf("%d", &a[i]);

  dp[n][0] = a[n];
  dp[n][1] = -a[n];

  for (int i = n - 1; i; i--) {
    ld c = 2 + (dp[i + 1][1] - dp[i + 1][0]) / a[i];
    dp[i][0] = -a[i] + dp[i + 1][0] + a[i] * max(c, (ld)0);
    dp[i][1] = a[i] + dp[i + 1][1] + a[i] * min(-c, (ld)0);
  }

  cout << fixed << setprecision(10) << dp[1][0] << endl;

  return 0;
}