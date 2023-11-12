#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
const int bits = 30;

int n, m;
vector<tuple<int, int, int>> edges;
vector<int> adj[N];

int p[bits][N];
int root(int v, int bit) {
  return p[bit][v] == v ? v : (p[bit][v] = root(p[bit][v], bit));
}
void merge(int u, int v, int bit) {
  u = root(u, bit);
  v = root(v, bit);
  if (u != v) p[bit][v] = u;
}

bool vis[bits][N];
bool one[N];

void dfs(int at, int bit) {
  one[at] = true;
  if (!vis[bit][at]) {
    vis[bit][at] = true;
    for (int edge : adj[at]) {
      auto [u, v, w] = edges[edge];
      if (w >> bit & 1) dfs(u + v - at, bit);
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;

  for (int i = 0; i < m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    u--, v--;
    adj[u].emplace_back(i);
    adj[v].emplace_back(i);
    edges.emplace_back(u, v, w);
  }

  for (int bit = 0; bit < bits; bit++) {
    iota(p[bit], p[bit] + n, 0);
  }

  for (auto [u, v, w] : edges) {
    for (int bit = 0; bit < bits; bit++) {
      if (w >> bit & 1) {
        merge(u, v, bit);
      }
    }
  }

  for (auto [u, v, w] : edges) {
    if ((w & 1) == 0) {
      for (int bit = 1; bit < bits; bit++) {
        dfs(u, bit);
        dfs(v, bit);
      }
    }
  }

  int q;
  cin >> q;

  while (q--) {
    int u, v;
    cin >> u >> v;
    u--, v--;

    int mex = -1;

    for (int bit = 0; bit < bits; bit++) {
      if (root(u, bit) == root(v, bit)) {
        mex = 0;
        break;
      }
    }

    if (mex == -1) {
      if (one[u]) mex = 1;
      else mex = 2;
    }

    cout << mex << "\n";
  }

  return 0;
}