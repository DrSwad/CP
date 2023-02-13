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

  int n, m, s, t;
  cin >> n >> m  >> s >> t;
  s--, t--;

  vector<vector<int>> e(n);
  vector<int> from, to, cap, flow;

  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;

    from.push_back(u);
    to.push_back(v);
    cap.push_back(1);
    flow.push_back(0);
    e[u].push_back(from.size() - 1);

    from.push_back(v);
    to.push_back(u);
    cap.push_back(1);
    flow.push_back(1);
    e[v].push_back(from.size() - 1);
  }

  function<vector<int>(void)> bfs = [&]() {
    vector<int> back(n, -1);
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
      int at = q.front();
      q.pop();
      for (int ei : e[at]) {
        if (!flow[ei]) {
          int v = to[ei];
          if (back[v] == -1) {
            back[v] = ei;
            q.push(v);
          }
        }
      }
    }

    vector<int> path;
    int at = t;
    while (at != s) {
      path.push_back(back[at]);
      at = from[back[at]];
    }

    reverse(path.begin(), path.end());
    return path;
  };

  vector<int> path[2];
  for (int it = 0; it < 2; it++) {
    path[it] = bfs();
    if (it == 0) {
      for (int ei : path[it]) {
        flow[ei]++;
        flow[ei ^ 1]--;
      }
    }
  }

  if (path[0].empty() or path[1].empty()) cout << "NO\n";
  else {
    cout << "YES\n";

    vector<int> ans[2];

    int i = 0, j = 0;
    while (j < path[1].size()) {
      int ei = path[1][j];
      if (ei & 1) {
        int u = from[ei ^ 1];
        int v = to[ei ^ 1];
        while (from[path[0][i]] != u) {
          ans[0].push_back(path[0][i++]);
        }
        j++;
        i++;
        swap(i, j);
        swap(path[0], path[1]);
      }
      else {
        ans[1].push_back(path[1][j]);
        j++;
      }
    }
    while (i < path[0].size()) ans[0].push_back(path[0][i++]);

    for (int it = 0; it < 2; it++) {
      for (int i = 0; i < ans[it].size(); i++) {
        if (i) cout << " ";
        cout << from[ans[it][i]] + 1;
      }
      cout << " " << t + 1;
      cout << "\n";
    }
  }

  return 0;
}