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
// All the edges must be from one part to the other