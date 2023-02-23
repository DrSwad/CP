#include <bits/stdc++.h>
using namespace std;

class HopcroftKarp {
public:
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
// All the edges must be from one part to the other

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int m;
  cin >> m;

  string s;
  cin >> s;
  int n = s.length();

  vector<vector<int>> e(n + m);

  vector<string> t(m);
  for (string &tt : t) cin >> tt;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (find(t[j].begin(), t[j].end(), s[i]) != t[j].end()) {
        e[i].push_back(n + j);
      }
    }
  }

  HopcroftKarp HK(e);
  if (HK.solve() < n) cout << "NO\n";
  else {
    cout << "YES\n";
    for (int i = 0; i < n; i++) {
      if (i) cout << " ";
      cout << (HK.match[i + 1] - n);
    }
    cout << "\n";
  }

  return 0;
}