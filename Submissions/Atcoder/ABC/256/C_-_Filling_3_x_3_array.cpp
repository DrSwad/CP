#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  const int MX = 30;

  int h[3];
  cin >> h[0] >> h[1] >> h[2];
  int w1, w2, w3;
  cin >> w1 >> w2 >> w3;

  vector<vector<vector<long long>>> dp(w1 + 1, vector(w2 + 1, vector(w3 + 1, 0ll)));
  dp[0][0][0] = 1;

  for (int i = 0; i < 3; i++) {
    vector<vector<vector<long long>>> ndp(w1 + 1, vector(w2 + 1, vector(w3 + 1, 0ll)));
    for (int s1 = 0; s1 <= w1; s1++) {
      for (int v1 = 1; v1 <= w1 - s1; v1++) {
        for (int s2 = 0; s2 <= w2; s2++) {
          for (int v2 = 1; v2 <= w2 - s2; v2++) {
            for (int s3 = 0; s3 <= w3; s3++) {
              for (int v3 = 1; v3 <= w3 - s3; v3++) {
                if (v1 + v2 + v3 == h[i]) {
                  ndp[s1 + v1][s2 + v2][s3 + v3] += dp[s1][s2][s3];
                }
              }
            }
          }
        }
      }
    }
    swap(dp, ndp);
  }

  cout << dp[w1][w2][w3] << "\n";

  return 0;
}