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

void test_case() {
  int n;
  cin >> n;

  vector<string> init_states(n);
  for (string &row : init_states) cin >> row;

  vector<int> ans;

  for (int i = 0; i < n; i++) {
    // debug(i);
    // DB();

    vector<string> states = init_states;
    int points = 0;
    for (int j = 0; j < n; j++) {
      if (states[i][j] == '.') {
        states[i][j] = '1';
        states[j][i] = '0';
      }

      if (states[i][j] == '1') points += 2;
      else if (states[i][j] == 'd') points++;
    }

    int node = 0;
    int src = node++;
    vector<tuple<int, int, int>> games;
    for (int j = 0; j < n; j++) {
      for (int k = j + 1; k < n; k++) {
        if (j != i and k != i) {
          games.push_back({node++, j, k});
        }
      }
    }
    vector<int> players(n);
    for (int j = 0; j < n; j++) {
      if (j != i) players[j] = node++;
    }
    int snk = node++;

    // debug(src);
    // debug(games);
    // debug(players);
    // debug(snk);
    // debug(node);

    Dinic dinic(node);
    for (auto [game_node, p1, p2] : games) {
      int w1, w2;
      if (states[p1][p2] == '1') w1 = 2, w2 = 0;
      else if (states[p1][p2] == '0') w1 = 0, w2 = 2;
      else if (states[p1][p2] == 'd') w1 = 1, w2 = 1;
      else if (states[p1][p2] == '.') w1 = 2, w2 = 2;
      else assert(false);
      // debug(game_node, p1, p2);
      // debug(players[p1], players[p2]);
      dinic.AddEdge(src, game_node, 2);
      dinic.AddEdge(game_node, players[p1], w1);
      dinic.AddEdge(game_node, players[p2], w2);
    }
    for (int j = 0; j < n; j++) {
      if (j != i) {
        int w = states[j][i] == '1' ? 2 : states[j][i] == 'd' ? 1 : 0;
        dinic.AddEdge(players[j], snk, points - w);
      }
    }

    int flow = dinic.MaxFlow(src, snk);
    // debug(flow);
    if (flow == 2 * games.size()) {
      ans.push_back(i);
    }
  }

  for (int i = 0; i < ans.size(); i++) {
    if (i) cout << " ";
    cout << ans[i] + 1;
  }
  cout << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}