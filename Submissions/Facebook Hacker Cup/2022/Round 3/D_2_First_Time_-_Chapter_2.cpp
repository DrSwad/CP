#include <bits/stdc++.h>
using namespace std;

void test_case() {
  // DB();
  int n, m;
  cin >> n >> m;

  vector<pair<int, int>> edges;
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    a--, b--;
    edges.emplace_back(a, b);
  }

  vector<vector<int>> remove_at(m);
  vector<vector<int>> comp(n);
  for (int i = 0; i < n; i++) comp[i].push_back(i);
  vector<int> color(n);
  iota(color.begin(), color.end(), 0);
  vector<int> real_color(n);
  iota(real_color.begin(), real_color.end(), 0);

  for (int i = 0; i < m; i++) {
    auto [a, b] = edges[i];
    int ra = real_color[a];
    int rb = real_color[b];
    // debug(ra, rb, comp[ra], comp[rb]);
    if (comp[ra].size() <= comp[rb].size()) {
      for (int j : comp[ra]) {
        comp[rb].push_back(j);
        if (j > 0 and color[j - 1] == rb) {
          remove_at[i].push_back(j);
        }
        if (j < n - 1 and color[j + 1] == rb) {
          remove_at[i].push_back(j + 1);
        }
      }
      for (int j : comp[ra]) color[j] = rb;
      comp[ra].clear();
    }
    else {
      for (int j : comp[rb]) {
        comp[ra].push_back(j);
        if (j > 0 and color[j - 1] == ra) {
          remove_at[i].push_back(j);
        }
        if (j < n - 1 and color[j + 1] == ra) {
          remove_at[i].push_back(j + 1);
        }
      }
      for (int j : comp[rb]) color[j] = ra;
      comp[rb].clear();
      swap(real_color[a], real_color[b]);
    }
    // debug(i, remove_at[i]);
  }

  vector<int> g(m + 1);
  {
    g[m] = 0;
    vector<bool> vis(n, true);
    for (int i = 0; i < m; i++) {
      for (int j : remove_at[i]) {
        vis[j] = false;
      }
    }
    for (int i = 0; i < n; i++) {
      if (vis[i]) {
        g[m] = gcd(g[m], i);
      }
    }
  }
  for (int i = m - 1; i >= 0; i--) {
    g[i] = g[i + 1];
    for (int j : remove_at[i]) {
      g[i] = gcd(g[i], j);
    }
  }

  // debug(g);

  vector<int> ans(n);
  for (int k = 1; k <= n; k++) {
    int L = -1, R = m + 1;
    while (R > L + 1) {
      int mid = (L + R) / 2;
      if (g[mid] % k == 0) R = mid;
      else L = mid;
    }
    ans[k - 1] = R > m ? -1 : R;
  }

  long long sum = 0;
  for (int i : ans) sum += i;

  cout << sum << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}