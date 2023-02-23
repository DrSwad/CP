#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  int m;
  cin >> m;
  vector<vector<int>> e(n);
  while (m--) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    e[u].push_back(v);
    e[v].push_back(u);
  }

  vector<int> dist(n, n);
  dist[0] = 0;
  queue<int> q;
  q.push(0);

  while (!q.empty()) {
    int v = q.front();
    q.pop();
    for (int u : e[v]) {
      if (dist[u] == n) {
        dist[u] = dist[v] + 1;
        q.push(u);
      }
    }
  }

  int mx_dist = *max_element(dist.begin(), dist.end());
  if (mx_dist == n) {
    cout << "-1\n";
    return 0;
  }

  int upd_moves = mx_dist == 1 ? 0 : 32 - __builtin_clz(mx_dist - 1);
  cout << upd_moves + 1 << "\n";

  return 0;
}