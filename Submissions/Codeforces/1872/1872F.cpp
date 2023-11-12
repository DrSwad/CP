#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  vector<vector<int>> ia(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    a[i]--;
    ia[a[i]].push_back(i);
  }

  vector<int> c(n);
  for (int &i : c) cin >> i;

  vector<vector<int>> cycles;
  vector<int> state(n, 0);

  vector<int> path;
  function<void(int)> dfs =
    [&](int at) {
      state[at] = 1;
      path.push_back(at);

      int to = a[at];
      if (state[to] == 0) dfs(to);
      else if (state[to] == 1) {
        cycles.push_back({});
        while (!path.empty() and path.back() != to) {
          cycles.back().push_back(path.back());
          path.pop_back();
        }
        assert(!path.empty());
        cycles.back().push_back(path.back());
      }

      state[at] = 2;
    };

  for (int i = 0; i < n; i++) {
    if (state[i] == 0) {
      path.clear();
      dfs(i);
    }
  }

  vector<int> p;
  vector<bool> vis(n, false);

  function<void(int)> dfs2 =
    [&](int at) {
      vis[at] = true;
      for (int to : ia[at]) {
        if (!vis[to]) {
          dfs2(to);
        }
      }
      p.push_back(at);
    };

  for (auto &cycle : cycles) {
    int min_cost = INT_MAX, min_at = -1;
    for (int i : cycle) {
      if (c[i] < min_cost) {
        min_cost = c[i];
        min_at = i;
      }
    }
    dfs2(min_at);
  }

  for (int i = 0; i < n; i++) {
    if (i) cout << " ";
    cout << p[i] + 1;
  }
  cout << "\n";
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