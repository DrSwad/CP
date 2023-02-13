#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<vector<int>> e(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    e[u].push_back(v);
    e[v].push_back(u);
  }

  function<pair<int, int>(int, int)> dfs = [&](int at, int from) {
    int sz = 1;
    vector<pair<int, int>> res;
    for (int to : e[at]) {
      if (to != from) {
        auto got = dfs(to, at);
        res.push_back(got);
        sz += got.first;
      }
    }

    if (res.empty()) return make_pair(sz, 0);
    else if (res.size() == 1) return make_pair(sz, res[0].first - 1);
    else {
      int ans1 = (res[0].first - 1) + (res[1].second);
      int ans2 = (res[0].second) + (res[1].first - 1);
      return make_pair(sz, max(ans1, ans2));
    }
  };

  cout << dfs(0, -1).second << "\n";
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