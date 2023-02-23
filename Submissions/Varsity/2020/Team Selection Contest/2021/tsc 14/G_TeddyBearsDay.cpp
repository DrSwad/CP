#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    scanf("%d", &n);

    vector<vector<pair<int, int>>> e(n);
    for (int i = 0; i < n - 1; i++) {
      int u, v, w;
      scanf("%d %d %d", &u, &v, &w);
      u--, v--;

      e[u].emplace_back(v, w);
      e[v].emplace_back(u, w);
    }

    vector<int> cnt(n, 0);
    int q;
    scanf("%d", &q);
    while (q--) {
      int u, v;
      scanf("%d %d", &u, &v);
      u--, v--;

      cnt[u]++;
      cnt[v]--;
    }

    function<void(int, int)> dfs1 = [&](int at, int from) {
      for (auto [to, w] : e[at]) {
        if (to != from) {
          dfs1(to, at);
          cnt[at] += cnt[to];
        }
      }
    };

    dfs1(0, -1);

    long long ans = 0;
    function<void(int, int, int)> dfs2 = [&](int at, int from,
                                             int fromW) {
      ans += abs((long long)cnt[at]) * fromW;

      for (auto [to, w] : e[at]) {
        if (to != from) { dfs2(to, at, w); }
      }
    };

    dfs2(0, -1, 0);

    printf("%lld\n", ans);
  }

  return 0;
}