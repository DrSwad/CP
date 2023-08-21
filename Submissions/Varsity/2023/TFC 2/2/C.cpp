#include <bits/stdc++.h>
using namespace std;

const int C = 26;
const int INF = int(1e9) + 5;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  string a, b;
  cin >> a >> b;

  vector next_a(n, vector(C, n));
  vector next_b(n, vector(C, n));
  for (int c = 0; c < C; c++) {
    for (int i = n - 1; i >= 0; i--) {
      next_a[i][c] = a[i] == 'a' + c ? i : i + 1 < n ? next_a[i + 1][c] : i + 1;
      next_b[i][c] = b[i] == 'a' + c ? i : i + 1 < n ? next_b[i + 1][c] : i + 1;
    }
  }

  vector dp(n, vector(n, vector(C, pair<int, int>(0, 0))));
  vector lcs(n, vector(n, pair<int, int>(0, 0)));

  for (int ia = n - 1; ia >= 0; ia--) {
    for (int ib = n - 1; ib >= 0; ib--) {
      for (int c = 0; c < C; c++) {
        int ja = next_a[ia][c], jb = next_b[ib][c];
        if (ja >= n or jb >= n) {
          dp[ia][ib][c] = {0, 0};
        }
        else {
          if (ja + 1 >= n or jb + 1 >= n) {
            dp[ia][ib][c] = {1, 1};
          }
          else {
            dp[ia][ib][c] = {lcs[ja + 1][jb + 1].first + 1, lcs[ja + 1][jb + 1].second};
          }
        }

        if (dp[ia][ib][c].first > lcs[ia][ib].first) {
          lcs[ia][ib] = dp[ia][ib][c];
        }
        else if (dp[ia][ib][c].first == lcs[ia][ib].first) {
          lcs[ia][ib].second = min(INF, lcs[ia][ib].second + dp[ia][ib][c].second);
        }
      }

      if (lcs[ia][ib].first == 0) lcs[ia][ib].second = 1;
    }
  }

  if (k > lcs[0][0].second) cout << "-1\n";
  else {
    int ia = 0, ib = 0;
    while (k) {
      if (k == 1) {
        if (ia >= n or ib >= n or lcs[ia][ib].first == 0) break;
      }

      assert(ia < n and ib < n);
      assert(lcs[ia][ib].second >= k);

      int c;
      for (c = 0; c < C; c++) {
        if (dp[ia][ib][c].first == lcs[ia][ib].first) {
          if (dp[ia][ib][c].second < k) {
            k -= dp[ia][ib][c].second;
          }
          else break;
        }
      }
      assert(c < C);

      cout << (char)('a' + c);
      ia = next_a[ia][c] + 1;
      ib = next_b[ib][c] + 1;
    }
    cout << "\n";
  }

  return 0;
}