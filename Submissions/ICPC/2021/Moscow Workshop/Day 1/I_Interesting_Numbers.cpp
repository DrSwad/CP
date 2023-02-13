#include <bits/stdc++.h>
using namespace std;

const int D = 20;

int dp[1 << D][D];

void test_case() {
  int n, k;
  cin >> n >> k;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  int ans = 0;

  for (int i = 0; i < n; i++) {
    int curr = a[i] <= k;

    for (int d = D - 1, pref = 0; d >= 0; d--) {
      if ((k >> d & 1) == 0) {
        if ((a[i] >> d & 1) == 1) {
          pref |= 1 << d;
        }
      }
      else {
        if ((a[i] >> d & 1) == 1) {
          curr = max(curr, 1 + dp[pref | 1 << d][d]);
        }
        else {
          curr = max(curr, 1 + dp[pref][d]);
          pref |= 1 << d;
        }
      }
    }

    curr = max(curr, 1 + dp[k ^ a[i]][0]);
    ans = max(ans, curr);

    for (int d = D - 1; d >= 0; d--) {
      int v = a[i] >> d;
      dp[v][d] = max(dp[v][d], curr);
    }
  }

  cout << ans << "\n";

  for (int i = 0; i < n; i++) {
    for (int d = D - 1; d >= 0; d--) {
      int v = a[i] >> d;
      dp[v][d] = -1;
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  memset(dp, -1, sizeof dp);

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}