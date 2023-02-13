#include <bits/stdc++.h>
using namespace std;

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

void test_case() {
  int n, m;
  cin >> n >> m;

  vector<pair<int, int>> rooks(m);
  for (auto & [x, y] : rooks) {
    cin >> x >> y;
    x--, y--;
  }

  int min_rooks = 0;
  {
    int nn = 2 * n;
    vector<vector<int>> e(nn);
    for (auto [x, y] : rooks) {
      e[x].push_back(n + y);
      e[n + y].push_back(x);
    }

    vector<bool> vis(nn, false);
    function<int(int)> dfs = [&](int at) {
      if (vis[at]) return 0;
      vis[at] = true;
      int ret = 1;
      for (int to : e[at]) {
        ret += dfs(to);
      }
      return ret;
    };
    for (int i = 0; i < nn; i++) {
      if (!vis[i]) {
        min_rooks += dfs(i) != 1;
      }
    }
  }

  int max_rooks = 0;
  {
    int nn = 2 * n;
    vector<vector<int>> e(nn);
    for (auto [x, y] : rooks) {
      e[x].push_back(n + y);
      e[n + y].push_back(x);
    }

    max_rooks = HopcroftKarp(e).solve();
  }

  cout << m - max_rooks << " " << m - min_rooks << "\n";
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