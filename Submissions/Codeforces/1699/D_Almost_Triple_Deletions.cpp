#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i, i--;

  vector<vector<int>> pos(n);
  for (int i = 0; i < n; i++) {
    pos[a[i]].push_back(i);
  }

  vector<vector<bool>> gone(n, vector<bool>(n));
  for (int l = 0; l < n; l++) {
    vector<int> freq(n, 0);
    int mx_freq = 0;
    for (int r = 0; r < n; r++) {
      if (r < l) gone[l][r] = true;
      else {
        freq[a[r]]++;
        mx_freq = max(mx_freq, freq[a[r]]);
        if ((r - l + 1) & 1) gone[l][r] = false;
        else gone[l][r] = mx_freq <= (r - l + 1) / 2;
      }
    }
  }

  int ans = 0;
  for (int v = 0; v < n; v++) {
    int sz = pos[v].size();
    if (sz == 0) continue;

    vector<int> dp(sz, 0);
    dp[0] = pos[v][0] == 0 or gone[0][pos[v][0] - 1];

    for (int i = 1; i < pos[v].size(); i++) {
      dp[i] = gone[0][pos[v][i] - 1];
      for (int j = 0; j < i; j++) {
        if (dp[j] and gone[pos[v][j] + 1][pos[v][i] - 1]) {
          dp[i] = max(dp[i], 1 + dp[j]);
        }
      }
    }

    for (int i = 0; i < sz; i++) {
      if (pos[v][i] == n - 1 or gone[pos[v][i] + 1][n - 1]) {
        ans = max(ans, dp[i]);
      }
    }
  }
  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}