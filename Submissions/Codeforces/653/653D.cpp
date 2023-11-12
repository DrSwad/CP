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
/*
   Dinic dinic(N);
   dinic.AddEdge(u - 1, v - 1, cap);
   dinic.AddEdge(v - 1, u - 1, cap);
   dinic.MaxFlow(0, N - 1);
 */

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m, x;
  cin >> n >> m >> x;

  vector<tuple<int, int, int>> edges(m);
  for (auto & [from, to, w] : edges) {
    cin >> from >> to >> w;
  }

  function<bool(double)> check =
    [&](double xi) {
      Dinic dinic(n + 1);
      for (auto [from, to, w] : edges) {
        dinic.AddEdge(from, to, w / xi);
      }
      dinic.AddEdge(0, 1, x);
      return dinic.MaxFlow(0, n) == x;
    };

  double L = 0, R = 1e6;
  for (int trial = 0; trial < 100; trial++) {
    double mid = (L + R) / 2;
    if (check(mid)) L = mid;
    else R = mid;
  }

  cout << fixed << setprecision(10) << x * L << "\n";

  return 0;
}