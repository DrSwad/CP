#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<vector<int>> e(n);
  for (int i = 1; i < n; i++) {
    int p;
    cin >> p;
    e[p - 1].push_back(i);
  }

  vector<int> longest_path_dp(n, 0);
  vector<int> ans_dp(n, 0);

  function<void(int, int)> dfs = [&](int at, int from) {
    longest_path_dp[at] = 1;
    for (int to : e[at]) {
      if (to == from) continue;
      dfs(to, at);
      longest_path_dp[at] = max(longest_path_dp[at], longest_path_dp[to] + 1);
      ans_dp[at] += ans_dp[to];
    }
    ans_dp[at] = max(ans_dp[at], longest_path_dp[at]);
  };

  dfs(0, -1);

  cout << ans_dp[0] << "\n";

  return 0;
}