#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

vector<int> g[N];
int h[N], p[N], jump[N];

void go(int u, int par = -1) {
  for (int v : g[u]) {
    if (v != par) {
      p[v] = u, h[v] = h[u] + 1;
      int x = jump[u], y = jump[x];
      jump[v] = (h[u] + h[y] == h[x] << 1) ? y : u;
      go(v, u);
    }
  }
}

int lca(int u, int v) {
  if (h[u] < h[v]) swap(u, v);
  while (h[u] > h[v]) u = h[jump[u]] < h[v] ? p[u] : jump[u];
  while (u != v) (jump[u] != jump[v]) ? (u = jump[u], v = jump[v]) : (u = p[u], v = p[v]);
  return u;
}

int main() {
  int root = 1;
  p[root] = h[root] = 0, jump[root] = root;
  go(root);

  return 0;
}