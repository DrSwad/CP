#include <bits/stdc++.h>
using namespace std;

const int N = 2e3 + 5;
const int M = 100 + 5;

int n;
vector<pair<int, int>> edge[N];
int need[N];
int dp[N][M];

void dfs(int at) {
  vector<int> sub_dp(M, 0);
  for (auto [to, cap] : edge[at]) {
    dfs(to);

    vector<int> new_sub_dp(M, 0);
    for (int pow_prev = 0; pow_prev < M; pow_prev++) {
      for (int pow_child = 0; pow_child <= cap; pow_child++) {
        int pow_total = pow_prev + pow_child;
        if (pow_total < M) {
          new_sub_dp[pow_total] = max(new_sub_dp[pow_total], sub_dp[pow_prev] + dp[to][pow_child]);
        }
      }
    }

    swap(sub_dp, new_sub_dp);
  }

  for (int p = 0; p < M; p++) {
    dp[at][p] = sub_dp[p];
    if (p >= need[at]) {
      dp[at][p] = max(dp[at][p], sub_dp[p - need[at]] + 1);
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;

  for (int i = 1; i <= n; i++) {
    int p, r, c;
    cin >> p >> r >> c;
    edge[p].push_back({i, c});
    need[i] = r;
  }

  need[0] = M;
  dfs(0);

  int ans = 0;
  for (auto [to, cap] : edge[0]) {
    ans += dp[to][cap];
  }

  cout << ans << "\n";

  return 0;
}