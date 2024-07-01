/*
   dp[i][w] = when w > 0, min cost for sub-tree of node i when it's parent edge has a weight of w
   dp[i][0] = min(dp[i][w]) for all w > 0
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, c; // 1 <= n <= 2e4, 1 <= c <= 1e5
  cin >> n >> c;

  if (n == 1) {
    cout << "0\n";
    return 0;
  }

  int max_w = 0;

  vector<vector<pair<int, int>>> e(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v, s; // 1 <= s <= 1e5
    cin >> u >> v >> s;
    u--, v--;
    e[u].emplace_back(v, s);
    e[v].emplace_back(u, s);
    max_w = max(max_w, s);
  }

  vector<int> sub_dp(n, 1);

  auto sub_dfs =
    [&](auto &&sub_dfs, int at, int from) -> void {
      for (auto [child, child_w] : e[at]) {
        if (child != from) {
          sub_dfs(sub_dfs, child, at);
          sub_dp[at] += sub_dp[child];
        }
      }
    };

  sub_dfs(sub_dfs, 0, -1);

  int max_logn = log2(n) + 2;
  vector<vector<int>> dp(max_logn, vector<int>(max_w + 1));
  stack<int> available_dps;
  vector<int> dpi(n, -1);
  for (int i = 0; i < max_logn; i++) available_dps.push(i);

  auto dfs =
    [&](auto&&dfs, int at, int from, int from_w) -> void {
      // Leaf node
      int children = e[at].size() - (at != 0);
      if (children == 0) {
        assert(!available_dps.empty());
        dpi[at] = available_dps.top();
        available_dps.pop();

        for (int w = 0; w <= max_w; w++) {
          assert(from_w != -1);
          dp[dpi[at]][w] =
            w == 0 ? 0
            : w < from_w ? -1
            : w - from_w;
        }
        return;
      }

      int max_child = max_element(
        e[at].begin(),
        e[at].end(),
        [&](auto a, auto b) {
          return sub_dp[a.first] < sub_dp[b.first];
        }
                      ) - e[at].begin();

      swap(e[at][0], e[at][max_child]);

      for (auto [child, child_w] : e[at]) {
        if (child != from) {
          dfs(dfs, child, at, child_w);

          if (dpi[at] == -1) {
            assert(!available_dps.empty());
            dpi[at] = available_dps.top();
            available_dps.pop();

            for (int w = 0; w <= max_w; w++) {
              dp[dpi[at]][w] = 0;
            }
          }

          for (int w = 0; w <= max_w; w++) {
            if (dp[dpi[at]][w] == -1 or dp[dpi[child]][w] == -1) {
              dp[dpi[at]][w] = -1;
            }
            else {
              dp[dpi[at]][w] += dp[dpi[child]][w];
            }
          }

          available_dps.push(dpi[child]);
          dpi[child] = -1;
        }
      }

      for (int w = 1; w <= max_w; w++) {
        if (from_w != -1 and w < from_w) dp[dpi[at]][w] = -1;
        else {
          if (dp[dpi[at]][w] != -1) {
            dp[dpi[at]][w] += from_w == -1 ? 0 : w - from_w;
          }
          else {
            dp[dpi[at]][w] = INT_MAX;
          }

          dp[dpi[at]][w] = min(
            (long long) dp[dpi[at]][w],
            dp[dpi[at]][0]
            + (from_w == -1 ? 0 : w - from_w)
            + 1ll * c * (int)e[at].size()
          );
        }
      }

      dp[dpi[at]][0] = INT_MAX;
      for (int w = 1; w <= max_w; w++) {
        if (dp[dpi[at]][w] != -1) {
          dp[dpi[at]][0] = min(dp[dpi[at]][0], dp[dpi[at]][w]);
        }
      }

      assert(dp[dpi[at]][0] < INT_MAX);
    };

  dfs(dfs, 0, -1, -1);

  assert(dpi[0] != -1 and dp[dpi[0]][0] != -1);
  cout << dp[dpi[0]][0] << "\n";

  return 0;
}