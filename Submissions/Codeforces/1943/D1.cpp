#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, k, p;
  cin >> n >> k >> p;

  vector dp(k + 2, vector(k + 2, 0));
  for (int first = k; first >= 0; first--) {
    for (int second = first; second >= 0; second--) {
      dp[first][second] = dp[first][second + 1] + 1;
    }
  }

  for (int len = 3; len <= n + 1; len++) {
    vector ndp(k + 2, vector(k + 2, 0));

    for (int first = k; first >= 0; first--) {
      for (int second = k; second >= 0; second--) {
        ndp[first][second] = (ndp[first][second + 1]
                              + dp[second][max(second - first, 0)]) % p;
      }
    }

    swap(dp, ndp);
  }

  cout << dp[0][0] << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}