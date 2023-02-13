#include <bits/stdc++.h>

using namespace std;

const int N = 40010;
const int INF = 1e8 + 5;

vector <int> g[N]; 
int n, m, p, match[N], dist[N];

bool bfs() {
  queue <int> q; 
  for (int i = 1; i <= n; ++i) {
    if (!match[i]) dist[i] = 0, q.emplace(i);
    else dist[i] = INF;
  } 
  dist[0] = INF;
  while (!q.empty()) {
    int u = q.front(); q.pop();
    if (!u) continue; 
    for (int v : g[u]) {
      if (dist[match[v]] == INF) {
        dist[match[v]] = dist[u] + 1, 
        q.emplace(match[v]);
      }
    }
  } 
  return dist[0] != INF;    
}

bool dfs (int u) {
  if (!u) return 1; 
  for (int v : g[u]) {
    if (dist[match[v]] == dist[u] + 1 and dfs(match[v])) {
      match[u] = v, match[v] = u;
      return 1; 
    } 
  } 
  dist[u] = INF;
  return 0;
}

int hopcroftKarp() {
  int ret = 0; 
  while (bfs()) {
    for (int i = 1; i <= n; ++i) {
      ret += !match[i] and dfs(i);
    }
  }
  return ret;
}

int main() {
  cin >> n >> m;
  // Bipartite Graph
  while (m--) {
    int u, v;
    scanf("%d %d", &u, &v);
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }
  // Maximum Matching, Minimum Vertex Cover
  int ans = hopcroftKarp();
  // Maximum Independent Set
  int offset = n - ans; 
  cout << ans << " " << offset << '\n';
  return 0;
}

