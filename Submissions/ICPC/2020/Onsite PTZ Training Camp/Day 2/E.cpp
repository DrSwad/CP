#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, m;
  cin >> n >> m;

  vector<pair<int, int>> e;
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v, u--, v--;
    e.emplace_back(u, v);
  }

  int a, b;
  cin >> a >> b;
  a--, b--;

  function<bool(int, vector<pair<int, int>>, int, int)> check = [](int n, vector<pair<int, int>> e, int a, int b) {
    // bool flag = e.size() == 7;
    // if (flag) debug(n, e, a, b);

    vector<vector<int>> adj(n);
    for (auto [u, v] : e) {
      adj[u].push_back(v);
      adj[v].push_back(u);
    }

    vector<vector<int>> adj2_a(n);
    for (int u : adj[a]) {
      if (u == b) continue;
      for (int v : adj[u]) {
        if (v != a and v != b and adj2_a[v].size() < 5) {
          adj2_a[v].push_back(u);
        }
      }
    }

    vector<vector<int>> adj2_b(n);
    for (int u : adj[b]) {
      if (u == a) continue;
      for (int v : adj[u]) {
        if (v != b and v != a and adj2_b[v].size() < 5) {
          adj2_b[v].push_back(u);
        }
      }
    }

    for (auto [c, d] : e) {
      for (int it = 0; it < 2; it++) {
        if (c != a and c != b and d != a and d != b) {
          for (int u : adj2_a[c]) {
            for (int v : adj2_b[d]) {
              // if (flag) debug(a, u, c, d, v, b);
              if (u != v and u != d and v != c) return true;
            }
          }
        }
        swap(c, d);
      }
    }

    return false;
  };

  int l = 0, r = m + 1;
  while (r > l + 1) {
    int mid = (l + r) / 2;
    // debug(l, mid, r);
    if (check(n, vector<pair<int, int>>(e.begin(), e.begin() + mid), a, b)) r = mid;
    else l = mid;
    // debug(l, r);
  }

  cout << (r > m ? -1 : r) << "\n";
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