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

  int n;
  cin >> n;
  Dinic dinic(n);

  int m;
  cin >> m;
  for (int i = 0; i < m; i++) {
    int u, v, cap;
    cin >> u >> v >> cap;
    dinic.AddEdge(u - 1, v - 1, cap);
    dinic.AddEdge(v - 1, u - 1, cap);
  }

  ll flow = dinic.MaxFlow(0, n - 1);
  vector<int> ans_e;

  {
    vector<vector<pair<int, int>>> e(n);
    for (int i = 0; i < dinic.E.size(); i++) {
      const auto &edge = dinic.E[i];
      int u = edge.u, v = edge.v;
      int flow = edge.flow, cap = edge.cap;
      e[v].push_back({u, i});
    }

    queue<int> q;
    q.push(n - 1);
    vector<bool> vis(n, false);
    vis[n - 1] = true;
    while (!q.empty()) {
      int at = q.front();
      q.pop();
      for (auto [to, ei] : e[at]) {
        const auto &edge = dinic.E[ei];
        ll cap = edge.cap, flow = edge.flow;
        if (flow and flow == cap) {
          ans_e.push_back(ei / 4);
        }
        else if (flow and !vis[to]) {
          q.push(to);
          vis[to] = true;
        }
      }
    }
  }

  cout << ans_e.size() << " " << flow << "\n";
  sort(ans_e.begin(), ans_e.end());
  for (int i = 0; i < ans_e.size(); i++) {
    if (i) cout << " ";
    cout << ans_e[i] + 1;
  }
  cout << "\n";

  return 0;
}