#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<vector<int>> adj(n);
  for (int i = 1; i < n; i++) {
    int p;
    cin >> p;
    adj[p - 1].push_back(i);
  }

  long long ans = 0;
  function<int(int)> dfs =
    [&](int at) {
      int subtree_size = 1;
      vector<int> child_subs;
      for (int to : adj[at]) {
        int child_sub = dfs(to);
        child_subs.push_back(child_sub);
        subtree_size += child_sub;
      }

      vector<bool> possible(subtree_size, false);
      possible[0] = true;

      for (int child_sub : child_subs) {
        for (int sum = subtree_size - 1; sum >= 0; sum--) {
          if (sum >= child_sub) {
            possible[sum] = possible[sum] or possible[sum - child_sub];
          }
        }
      }

      int mx = 0;
      for (int sum = 1; sum <= (subtree_size - 1) / 2; sum++) {
        if (possible[sum]) mx = sum;
      }

      ans += 1ll * mx * (subtree_size - 1 - mx);

      return subtree_size;
    };

  dfs(0);

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  // cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}