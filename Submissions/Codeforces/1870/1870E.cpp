#include <bits/stdc++.h>
using namespace std;

const int N = 5e3 + 5;

int n;
int a[N];
bool dp[N][2 * N];
int mex[N][N];
bool vis[N];

void test_case() {
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];

  dp[0][0] = true;
  mex[0][0] = 0;

  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < 2 * n; j++) dp[i][j] = dp[i - 1][j];
    for (int i = 0; i <= n; i++) vis[i] = false;
    int cur_mex = 0;
    for (int j = i; j >= 1; j--) {
      vis[a[j]] = true;
      while (vis[cur_mex]) cur_mex++;
      mex[i][j] = cur_mex;

      if (mex[i][j] != mex[i - 1][j] and mex[i][j] != mex[i][j + 1]) {
        for (int prv_xor = 0; prv_xor < 2 * n; prv_xor++) {
          if (dp[j - 1][prv_xor]) {
            dp[i][prv_xor ^ cur_mex] = true;
          }
        }
      }
    }
  }

  int ans = 2 * n - 1;
  while (!dp[n][ans]) ans--;
  cout << ans << "\n";
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