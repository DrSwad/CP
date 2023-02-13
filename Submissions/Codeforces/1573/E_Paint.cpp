#include <bits/stdc++.h>
using namespace std;

const int N = 3e3 + 5;

int n;
int a[N];
int dp[N][N];
int prv[N];

void test_case() {
  cin >> n;

  map<int, int> lst;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    prv[i] = lst[a[i]];
    lst[a[i]] = i;
  }

  for (int len = 1; len <= n; len++) {
    for (int l = 1; l <= n - len + 1; l++) {
      int r = l + len - 1;

      dp[l][r] = 0;
      for (int R = r; R > l; ) {
        int nR = max(l - 1, prv[R]);
        if (nR < R - 1) {
          dp[l][r] += dp[nR + 1][R - 1] + 1;
        }
        R = nR;
      }
    }
  }

  cout << dp[1][n] << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}