#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  string s[3];
  cin >> s[0] >> s[1] >> s[2];

  vector<bool> movable(n + 2, false);
  for (int c = 1; c <= n - 1; c++) {
    for (int r = 0; r < 2; r++) {
      if (s[r][c - 1] == 'O' and s[r][c - 1 + 1] == 'O' and
          s[r + 1][c - 1] == 'O' and s[r + 1][c - 1 + 1] == 'O'
          ) {
        movable[c] = true;
      }
    }
  }

  vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));

  for (int len = 2; len <= n; len++) {
    for (int l = 1; l <= n + 1 - len; l++) {
      int r = l + len - 1;
      vector<int> g;
      for (int k = l; k < r; k++) {
        if (movable[k]) {
          g.push_back(dp[l][k - 1] ^ dp[k + 2][r]);
        }
      }
      sort(g.begin(), g.end());
      g.resize(unique(g.begin(), g.end()) - g.begin());
      int mex = 0;
      while (mex < g.size() and g[mex] == mex) mex++;
      dp[l][r] = mex;
    }
  }

  cout << (dp[1][n] ? "Jhinuk\n" : "Grandma\n");
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}