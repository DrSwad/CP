#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  int k = *max_element(a.begin(), a.end()) + 1;
  vector<vector<int>> nodes_with_color(k);
  for (int i = 1; i <= n; i++) {
    nodes_with_color[a[i - 1]].push_back(i);
  }

  assert(k > 1);

  if (k == 2 and (nodes_with_color[0].size() % 2 == 1 or nodes_with_color[1].size() % 2 == 1)) {
    cout << "-1\n";
  }
  else {
    vector<pair<int, int>> ans;

    if (k > 2) {
      for (int c1 = 0; c1 < k; c1++) {
        for (int c2 = c1 + 1; c2 < k; c2++) {
          for (int u : nodes_with_color[c1]) {
            for (int v : nodes_with_color[c2]) {
              if (c1 == 0 and c2 == k - 1) ans.emplace_back(v, u);
              else ans.emplace_back(u, v);
            }
          }
        }
      }
    }
    else {
      int sz0 = nodes_with_color[0].size();
      int sz1 = nodes_with_color[1].size();
      for (int i = 0; i < sz0; i++) {
        for (int j = 0; j < sz1; j++) {
          int u = nodes_with_color[0][i];
          int v = nodes_with_color[1][j];
          if (i / (sz0 / 2) == 0 and j / (sz1 / 2) != 0) swap(u, v);
          if (i / (sz0 / 2) != 0 and j / (sz1 / 2) == 0) swap(u, v);
          ans.emplace_back(u, v);
        }
      }
    }

    cout << ans.size() << "\n";
    for (auto [u, v] : ans) cout << u << " " << v << "\n";
  }
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