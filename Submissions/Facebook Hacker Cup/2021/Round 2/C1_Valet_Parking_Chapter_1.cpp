#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int r, c, k;
  cin >> r >> c >> k;
  k--;
  vector<string> g(r);
  for (string &s : g) cin >> s;

  vector<vector<vector<int>>> sum(2, vector<vector<int>>(r, vector<int>(c, 0)));

  for (int j = 0; j < c; j++) sum[0][0][j] = g[0][j] == 'X';
  for (int i = 1; i < r; i++) {
    for (int j = 0; j < c; j++) {
      sum[0][i][j] = sum[0][i - 1][j] + (g[i][j] == 'X');
    }
  }

  for (int j = 0; j < c; j++) sum[1][r - 1][j] = g[r - 1][j] == 'X';
  for (int i = r - 2; i >= 0; i--) {
    for (int j = 0; j < c; j++) {
      sum[1][i][j] = sum[1][i + 1][j] + (g[i][j] == 'X');
    }
  }

  // debug(sum);

  int ans = r * c;
  for (int i = -1; i <= r; i++) {
    int cnt = 0;
    for (int j = 0; j < c; j++) {
      bool flag = false;
      if (0 <= i and i < r and g[i][j] == 'X') flag = true;
      if (i < k and sum[1][max(i, 0)][j] >= r - k) flag = true;
      if (i > k and sum[0][min(i, r - 1)][j] >= k + 1) flag = true;
      cnt += flag;
      // debug(i, flag);
    }
    ans = min(ans, cnt + abs(i - k));
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}