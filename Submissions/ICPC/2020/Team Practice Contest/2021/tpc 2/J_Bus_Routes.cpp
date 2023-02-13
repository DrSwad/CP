#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

namespace mcmf {
using T = int;
const T INF = 0x3f3f3f3f;
const int MAX = 105;

int n, src, snk;
T dis[MAX], mCap[MAX];
int par[MAX], pos[MAX];
bool vis[MAX];

struct Edge {
  int to, rev_pos;
  T cap, cost, flow;
};

vector<Edge> ed[MAX];

void init(int _n, int _src, int _snk) {
  n = _n, src = _src, snk = _snk;
  for (int i = 1; i <= n; i++) ed[i].clear();
}

void addEdge(int u, int v, T cap, T cost) {
  Edge a = {v, (int)ed[v].size(), cap, cost, 0};
  Edge b = {u, (int)ed[u].size(), 0, -cost, 0};
  ed[u].push_back(a);
  ed[v].push_back(b);
}

inline bool SPFA() {
  memset(vis, false, sizeof vis);
  for (int i = 1; i <= n; i++) mCap[i] = dis[i] = INF;
  queue<int> q;
  dis[src] = 0;
  vis[src] = true;       /// src is in the queue now
  q.push(src);

  while (!q.empty()) {
    int u = q.front();
    q.pop();
    vis[u] = false;         /// u is not in the queue now
    for (int i = 0; i < (int)ed[u].size(); i++) {
      Edge &e = ed[u][i];
      int v = e.to;
      if (e.cap > e.flow && dis[v] > dis[u] + e.cost) {
        dis[v] = dis[u] + e.cost;
        par[v] = u;
        pos[v] = i;
        mCap[v] = min(mCap[u], e.cap - e.flow);
        if (!vis[v]) {
          vis[v] = true;
          q.push(v);
        }
      }
    }
  }
  return (dis[snk] != INF);
}

inline pair<T, T> solve() {
  T F = 0, C = 0, f;
  int u, v;
  while (SPFA()) {
    u = snk;
    f = mCap[u];
    F += f;
    while (u != src) {
      v = par[u];
      ed[v][pos[u]].flow += f;           // edge of v-->u increases
      ed[u][ed[v][pos[u]].rev_pos].flow -= f;
      u = v;
    }
    C += dis[snk] * f;
  }
  return make_pair(F, C);
}
}

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, v, w;
    scanf("%d %d %d", &n, &v, &w);

    mcmf::init(n + 2, 1, n + 2);
    vector<int> degree(n + 1, 0);

    for (int i = 0; i < v; i++) {
      int from, to;
      scanf("%d %d", &from, &to);
      degree[from]++;
      degree[to]--;
    }

    for (int i = 0; i < w; i++) {
      int from, to;
      scanf("%d %d", &from, &to);
      degree[from]++;
      degree[to]--;

      mcmf::addEdge(from + 1, to + 1, 1, 1);
    }

    int supply = 0;
    for (int i = 1; i <= n; i++) {
      supply += max(degree[i], 0);

      if (degree[i] > 0) mcmf::addEdge(1, i + 1, degree[i], 0);
      if (degree[i] < 0) mcmf::addEdge(i + 1, n + 2, -degree[i], 0);
    }

    auto got = mcmf::solve();
    int flow = got.first, cost = got.second;
    if (flow != supply) puts("-1");
    else printf("%d\n", cost);
  }

  return 0;
}