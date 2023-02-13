#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 3e2 + 5;

int n;
pair<int, int> candle[N];
ll dp[N][N][N][2];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> candle[i].first >> candle[i].second;
  }

  sort(candle + 1, candle + n + 1);

  for (int i = 1; i <= n; i++) {
    for (int rem = 0; rem < n; rem++) {
      for (int e = 0; e < 2; e++) {
        ll dist = abs(candle[i].first);
        ll contrib = dist * rem;
        dp[i][i][rem][e] = max(-contrib, -contrib + (candle[i].second - dist));
      }
    }
  }

  for (int len = 2; len <= n; len++) {
    for (int l = 1; l + len - 1 <= n; l++) {
      int r = l + len - 1;
      for (int rem = 0; rem + len <= n; rem++) {
        for (int e = 0; e < 2; e++) {
          ll &cdp = dp[l][r][rem][e];
          cdp = LLONG_MIN;
          pair<int, int> curr = candle[e == 0 ? l : r];

          for (int take = 0; take < 2; take++) {
            int L = l + (e == 0);
            int R = r - (e == 1);

            for (int ee = 0; ee < 2; ee++) {
              pair<int, int> prv = candle[ee == 0 ? L : R];
              ll dist = abs(curr.first - prv.first);
              ll contrib = dist * rem;
              int nrem = rem + take;

              cdp = max(cdp, dp[L][R][nrem][ee] - contrib + (curr.second - dist) * take);
            }
          }
        }
      }
    }
  }

  ll ans = 0;
  for (int c = 0; c <= n; c++) {
    ans = max(ans, dp[1][n][c][0]);
    ans = max(ans, dp[1][n][c][1]);
  }

  cout << ans << "\n";

  return 0;
}