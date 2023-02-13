#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, m, k;
  cin >> n >> m >> k;

  vector<pair<int, int>> edges;
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    a--, b--;
    edges.emplace_back(a, b);
  }

  function<bool(int)> check = [&](int m) {
    vector<vector<int>> comp(n);
    for (int i = 0; i < n; i++) comp[i].push_back(i);

    for (int i = 0; i < m; i++) {
      auto [a, b] = edges[i];
      if (comp[a].size() <= comp[b].size()) {
        for (int j : comp[a]) comp[b].push_back(j);
        comp[a].clear();
      }
      else {
        for (int j : comp[b]) comp[a].push_back(j);
        comp[b].clear();
        swap(comp[a], comp[b]);
      }
    }

    vector<int> color(n);
    for (int i = 0; i < n; i++) {
      for (int j : comp[i]) color[j] = i;
    }

    for (int st = 0; st < n; st += k) {
      int en = min(st + k, n);
      int c = color[st];
      for (int i = st; i < en; i++) {
        if (color[i] != c) {
          return false;
        }
      }
    }

    return true;
  };

  int L = -1, R = m + 1;
  while (R > L + 1) {
    int mid = (L + R) / 2;
    if (check(mid)) R = mid;
    else L = mid;
  }

  cout << (R > m ? -1 : R) << "\n";
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