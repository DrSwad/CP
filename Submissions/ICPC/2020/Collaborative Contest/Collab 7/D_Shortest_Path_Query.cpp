#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;
int n, m;
vector<tuple<int, int, int>> e;
vector<vector<int>> adj;
vector<vector<long long>> dist;

inline int nodeID(int root, int node) {
  assert(node >= root);
  int root_sz = 32 - __builtin_clz(root);
  int node_sz = 32 - __builtin_clz(node);
  return (node & ((1 << (node_sz - root_sz)) - 1)) | (1 << (node_sz - root_sz));
}

int dfs(int root) {
  if (root << 1 > n) {
    if (root <= n) {
      dist[root].resize(1, 0);
      return 1;
    }
    else return 0;
  }

  int tot = dfs(root << 1) + dfs(root << 1 | 1) + 1;
  priority_queue<pair<long long, int>> pq;
  pq.push({0, root});
  dist[root].resize(tot + 1, INF);
  dist[root][1] = 0;

  while (!pq.empty()) {
    auto [dst, at] = pq.top();
    dst = -dst;
    pq.pop();
    if (dist[root][nodeID(root, at)] < dst) continue;

    for (int toE : adj[at]) {
      auto [u, v, w] = e[toE];
      int to = u ^ v ^ at;
      if (to < root) continue;
      if (dist[root][nodeID(root, to)] <= dst + w) continue;
      dist[root][nodeID(root, to)] = dst + w;
      pq.push({-(dst + w), to});
    }
  }

  return tot;
}

int main() {
  scanf("%d %d", &n, &m);

  e.resize(m);
  adj.resize(n + 1);
  for (int i = 0; i < m; i++) {
    auto& [u, v, w] = e[i];
    scanf("%d %d %d", &u, &v, &w);
    adj[u].push_back(i);
    adj[v].push_back(i);
  }

  dist.resize(n + 1);
  dfs(1);

  int q;
  scanf("%d", &q);

  while (q--) {
    int u, v;
    scanf("%d %d", &u, &v);

    int u_sz = 32 - __builtin_clz(u);
    int v_sz = 32 - __builtin_clz(v);
    long long ans = INF;

    for (int i = 1, root = 0; i <= min(u_sz, v_sz); i++) {
      bool u_bit = u & 1 << (u_sz - i);
      bool v_bit = v & 1 << (v_sz - i);
      if (u_bit == v_bit) {
        root = root << 1 | u_bit;
        ans = min(ans, dist[root][nodeID(root, u)] + dist[root][nodeID(root, v)]);
      } else break;
    }

    if (ans == INF) puts("-1");
    else printf("%lld\n", ans);
  }

  return 0;
}