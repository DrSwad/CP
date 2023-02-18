#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  vector<int> len(2);
  vector<vector<pair<int, int>>> snake(2);
  for (int id = 0; id < 2; id++) {
    cin >> len[id];
    for (int i = 0; i < len[id]; i++) {
      int x, y;
      cin >> x >> y;
      snake[id].emplace_back(x, y);
    }
  }

  int ans = 0;

  for (int it = 0; it < 2; it++) {
    map<pair<int, int>, int> cell_index;
    for (int i = 0; i < len[1]; i++) {
      cell_index[snake[1][i]] = i;
    }

    vector<int> dp(len[0] + 1);
    dp[len[0]] = 0;

    for (int i = len[0] - 1; i >= 0; i--) {
      dp[i] = 0;
      if (cell_index.count(snake[0][i])) {
        dp[i] = 1;
        int index = cell_index[snake[0][i]];
        if (dp[i + 1] and cell_index[snake[0][i + 1]] == index + 1) {
          dp[i] += dp[i + 1];
        }
      }

      ans = max(ans, dp[i]);
    }

    reverse(snake[1].begin(), snake[1].end());
  }

  cout << ans << "\n";

  return 0;
}
