#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> x(n);
  vector<int> c(n);

  for (int &i : x) cin >> i, i--;
  for (int &i : c) cin >> i;

  vector<int> state(n, 0);
  vector<bool> cycle(n, false);

  function<void(int)> dfs1 = [&](int at) {
    if (state[at] == 2) return;
    if (state[at] == 1) {
      cycle[at] = true;
      return;
    }

    state[at] = 1;
    dfs1(x[at]);
    state[at] = 2;
  };

  for (int i = 0; i < n; i++) {
    if (state[i] == 0) {
      dfs1(i);
    }
  }

  vector<bool> vis(n, false);
  long long ans = 0;

  function<int(int)> dfs2 = [&](int at) {
    if (vis[at]) return c[at];
    vis[at] = true;
    return min(c[at], dfs2(x[at]));
  };

  for (int i = 0; i < n; i++) {
    if (cycle[i] and !vis[i]) {
      ans += dfs2(i);
    }
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}