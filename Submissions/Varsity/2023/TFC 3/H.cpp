#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, p;
  cin >> n >> p;

  vector<int> in_deg(n, 0), out_deg(n, 0);
  vector<vector<pair<int, int>>> adj(n);

  while (p--) {
    int a, b, d;
    cin >> a >> b >> d;
    a--, b--;
    adj[a].emplace_back(b, d);
    in_deg[b]++;
    out_deg[a]++;
  }

  vector<tuple<int, int, int>> ans;

  function<pair<int, int>(int)> dfs =
    [&](int at) {
      if (out_deg[at]) {
        auto [en, amount] = dfs(adj[at][0].first);
        amount = min(amount, adj[at][0].second);
        return pair<int, int>{en, amount};
      }
      else {
        return pair<int, int>{at, INT_MAX};
      }
    };

  for (int i = 0; i < n; i++) {
    if (out_deg[i] == 1 and in_deg[i] == 0) {
      int st = i;
      auto [en, amount] = dfs(st);
      ans.emplace_back(st, en, amount);
    }
  }

  cout << ans.size() << "\n";
  sort(ans.begin(), ans.end());
  for (auto [st, en, amount] : ans) {
    cout << st + 1 << " " << en + 1 << " " << amount << "\n";
  }

  return 0;
}