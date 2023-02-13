#include <bits/stdc++.h>

using namespace std;

const int MAX = 1e2 + 5;
int nn; bool isCentroid[MAX]; int sub[MAX]; // internal, won't need anymore
vector<int> g[MAX], ed[MAX]; // original graph adjacency list
vector<int> nodes_under[MAX];

set<int> alive;

void calcSubTree(int s, int p) {
  sub[s] = 1;
  for (int x : ed[s]) {
    if (x == p or isCentroid[x]) continue;
    calcSubTree(x, s);
    sub[s] += sub[x];
  }
}

int getCentroid(int s, int p) {
  for (int x : ed[s]) {
    if (!isCentroid[x] && x != p && sub[x] > (nn / 2)) return getCentroid(x, s);
  }
  return s;
}

int find_x(int root) {
  fill(sub, sub + MAX, 0);
  fill(isCentroid, isCentroid + MAX, 0);

  calcSubTree(root, -1);
  nn = sub[root];
  return getCentroid(root, -1);
}

set<int> good;

bool query(vector<int> vertices, int x) {
  cout << "? " << vertices.size() << ' ' << x << ' ';
  for (int i = 0; i < vertices.size(); i++) {
    cout << vertices[i] << " \n"[i + 1 == vertices.size()];
  }

  int ans;
  cin >> ans;
  return ans;
}

void build_graph(int n) {
  vector<bool> nice(n + 1, 0);
  for (auto u : alive) nice[u] = 1;
  for (auto u : alive) {
    for (auto v : g[u]) {
      if (nice[v]) {
        ed[u].push_back(v);
        // cout << u << ' ' << v << endl;
      }
    }
  }
}

void dfs(int u, int p = -1, int at = 0) {
  // cout << at << ' ' << u << endl;
  nodes_under[at].push_back(u);
  for (auto v : g[u]) {
    if (v == p) continue;
    dfs(v, u, at);
  }
}

void fuck(int x) {
  vector<int> child;
  fill(sub, sub + MAX, 0);
  for (auto v : ed[x]) {
    dfs(v, x, v);
  }

  int lo = 0, hi = ed[x].size() - 1;

  while (lo <= hi) {
    int mid = lo + hi >> 1;
    vector<int> query_nodes;
    for (int i = 0; i <= mid; i++) {
      for (auto u : nodes_under[ed[x][i]]) {
        if (u ^ x) query_nodes.push_back(u);
      }
    }

    if (query(query_nodes, x)) hi = mid;
    else lo = mid + 1;
  }

  for (auto u : alive) {
    nodes_under[u].clear();
  }

  alive.clear();
  alive.insert(x);
  for (auto u : ed[ed[x][lo]]) {
    alive.insert(u);
  }
}

int main() {

  int n, u, v;
  cin >> n;

  for (int i = 1; i <= n; i++) {
    alive.insert(i);
  }

  for (int i = 0; i < n - 1; i++) {
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  while (alive.size() > 2) {
    build_graph(n);
    int x = find_x(*alive.begin());
    fuck(x);
    n = alive.size();
  }

  int v1 = *alive.begin();
  int v2 = *alive.begin();

  vector<int> special;
  special.push_back(v1);
  if (query(special, v1) and query(special, v2)) {
    special[0] = v2;
  }

  cout << "! " << special[0] << endl;

  return 0;
}