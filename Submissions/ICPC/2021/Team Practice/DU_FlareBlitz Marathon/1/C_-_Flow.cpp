#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct edge {
  int u, v;
  ll cap, flow;
  edge() {}
  edge(int u, int v, ll cap) : u(u), v(v), cap(cap), flow(0) {}
};

struct Dinic {
  int N;
  vector<edge> E;
  vector<vector<int>> g;
  vector<int> d, pt;

  Dinic(int N) : N(N), E(0), g(N), d(N), pt(N) {}

  void AddEdge(int u, int v, ll cap) {
    if (u ^ v) {
      E.emplace_back(u, v, cap);
      g[u].emplace_back(E.size() - 1);
      E.emplace_back(v, u, 0);
      g[v].emplace_back(E.size() - 1);
    }
  }

  bool BFS(int S, int T) {
    queue<int> q({S});
    fill(d.begin(), d.end(), N + 1);
    d[S] = 0;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      if (u == T) break;
      for (int k : g[u]) {
        edge &e = E[k];
        if (e.flow<e.cap and d [e.v]> d[e.u] + 1) {
          d[e.v] = d[e.u] + 1;
          q.emplace(e.v);
        }
      }
    }
    return d[T] != N + 1;
  }

  ll DFS(int u, int T, ll flow = -1) {
    if (u == T or flow == 0) return flow;
    for (int &i = pt[u]; i < g[u].size(); ++i) {
      edge &e = E[g[u][i]];
      edge &oe = E[g[u][i] ^ 1];
      if (d[e.v] == d[e.u] + 1) {
        ll amt = e.cap - e.flow;
        if (flow != -1 and amt > flow) amt = flow;
        if (ll pushed = DFS(e.v, T, amt)) {
          e.flow += pushed;
          oe.flow -= pushed;
          return pushed;
        }
      }
    }
    return 0;
  }

  ll MaxFlow(int S, int T) {
    ll total = 0;
    while (BFS(S, T)) {
      fill(pt.begin(), pt.end(), 0);
      while (ll flow = DFS(S, T)) total += flow;
    }
    return total;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m, k;
  cin >> n >> m >> k;

  vector<int> end_freq(n + 1, 0);
  for (int i = 0; i < k; i++) {
    int b;
    cin >> b;
    end_freq[b]++;
  }

  vector<vector<int>> e(n + 1);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    if (v) e[u].push_back(v);
    if (u) e[v].push_back(u);
  }

  function<bool(int)> check = [&](int days) {
    Dinic dinic(1 + days * n + 1);
    int sink = 1 + days * n;
    for (int d = 1; d <= days; d++) {
      int offset = n * (d - 1);
      for (int to : e[0]) {
        dinic.AddEdge(0, offset + to, 1);
      }
    }
    for (int d = 1; d < days; d++) {
      int offset = n * (d - 1);
      for (int i = 1; i <= n; i++) {
        dinic.AddEdge(offset + i, (offset + n) + i, k);
        for (int j : e[i]) {
          dinic.AddEdge(offset + i, (offset + n) + j, 1);
        }
      }
    }
    for (int i = 1; i <= n; i++) {
      int offset = n * (days - 1);
      dinic.AddEdge(offset + i, sink, end_freq[i]);
    }
    return dinic.MaxFlow(0, sink) == k;
  };

  int min_days = 0, max_days = k * m;
  while (max_days - min_days > 1) {
    int days = (min_days + max_days) / 2;
    if (check(days)) max_days = days;
    else min_days = days;
  }

  cout << max_days << "\n";

  return 0;
}