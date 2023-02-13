#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

class HopcroftKarp {
private:
  const int INF = 1e8 + 5;
  int n;
  vector<vector<int>> g;
  vector<int> match, dist;
  bool bfs() {
    queue<int> q;
    for (int i = 1; i <= n; ++i) {
      if (!match[i]) dist[i] = 0, q.emplace(i);
      else dist[i] = INF;
    }
    dist[0] = INF;
    while (!q.empty()) {
      int u = q.front(); q.pop();
      if (!u) continue;
      for (int v : g[u - 1]) {
        v++;
        if (dist[match[v]] == INF) {
          dist[match[v]] = dist[u] + 1,
          q.emplace(match[v]);
        }
      }
    }
    return dist[0] != INF;
  }
  bool dfs(int u) {
    if (!u) return true;
    for (int v : g[u - 1]) {
      v++;
      if (dist[match[v]] == dist[u] + 1 and dfs(match[v])) {
        match[u] = v, match[v] = u;
        return true;
      }
    }
    dist[u] = INF;
    return false;
  }
public:
  HopcroftKarp(vector<vector<int>> g) : n(g.size()), g(g) {
    match.resize(n + 1, 0);
    dist.resize(n + 1, 0);
  }
  int solve() {
    int ret = 0;
    while (bfs()) {
      for (int i = 1; i <= n; ++i) {
        ret += !match[i] and dfs(i);
      }
    }
    return ret;
  }
};
// HopcroftKarp(e).solve(); // e = 0-indexed adjacency-list

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m, a, b;
  cin >> n >> m >> a >> b;
  int tot = n * m;

  int free = 0;
  vector<string> grid(n);
  for (string &row : grid) {
    cin >> row;
    free += count(row.begin(), row.end(), '*');
  }

  if (2 * b <= a) {
    int cost = b * free;
    cout << cost << "\n";
    return 0;
  }
  else {
    vector<vector<int>> e(tot);

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (grid[i][j] == '*') {
          int u = i * m + j;
          if (i < n - 1 and grid[i + 1][j] == '*') {
            int v1 = u, v2 = u + m;
            if ((i + j) & 1) swap(v1, v2);
            e[v1].push_back(v2);
          }
          if (j < m - 1 and grid[i][j + 1] == '*') {
            int v1 = u, v2 = u + 1;
            if ((i + j) & 1) swap(v1, v2);
            e[v1].push_back(v2);
          }
        }
      }
    }

    int matches = HopcroftKarp(e).solve();
    int cnt2 = matches;
    int cnt1 = free - cnt2 * 2;
    int cost = cnt1 * b + cnt2 * a;
    cout << cost << "\n";
  }

  return 0;
}