#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int n;
vector<pair<int, int>> e[N];
int dp[N][5];

int DP(int at, int from, int path_ends) {
  if (dp[at][path_ends] != -1) return dp[at][path_ends];

  vector<int> curr_dp(path_ends + 1, 0);
  for (auto [to, w] : e[at]) {
    if (to == from) continue;
    vector<int> nxt_dp(path_ends + 1, INT_MAX);
    for (int took = 0; took <= path_ends; took++) {
      for (int take = 0; take <= path_ends - took; take++) {
        nxt_dp[took + take] = min(nxt_dp[took + take], curr_dp[took] + DP(to, at, take) + (take & 1 ? w : 2 * w));
      }
    }
    swap(curr_dp, nxt_dp);
  }

  return dp[at][path_ends] = curr_dp[path_ends];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;

  for (int i = 0; i < n - 1; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    u--, v--;
    e[u].emplace_back(v, w);
    e[v].emplace_back(u, w);
  }

  memset(dp, -1, sizeof dp);
  cout << DP(0, -1, 4) << "\n";

  return 0;
}