#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<vector<pair<int, int>>> e(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    e[u].push_back({v, w});
    e[v].push_back({u, w});
  }

  vector<int> dist(n);
  function<void(int, int)> dfs = [&](int at, int from) {
    for (auto [to, w] : e[at]) {
      if (to != from) {
        dist[to] = dist[at] + w;
        dfs(to, at);
      }
    }
  };

  int diameter_start = 0, diameter_length;
  for (int it = 0; it < 2; it++) {
    dist[diameter_start] = 0;
    dfs(diameter_start, -1);
    diameter_start = max_element(dist.begin(), dist.end()) - dist.begin();
    diameter_length = dist[diameter_start];
  }

  cout << diameter_length << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}