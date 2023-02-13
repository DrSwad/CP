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

  if (n == 1) {
    puts("0");
    return;
  }

  {
    int mx = 0;
    for (int i = 0; i < n; i++) {
      mx = max(mx, (int)e[i].size());
    }
    if (mx <= 2) {
      puts("1\n");
      return;
    }
  }

  vector<bool> is_bamboo(n, false);
  auto dfs1 = [&](int at, int from) {
    is_bamboo[at] = e[at].size() <= 2;

    for (int to : e[at]) {
      if (to != from) {
        dfs1(to, at);
      }
    }

    if (at != 0) {}
  };
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