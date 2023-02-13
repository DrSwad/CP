#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int M = 1e5 + 5;
const int D = 42195 + 5;
const int L = 1000 + 5;

struct edge {
  int u, v, w;
  edge(int u = 0, int v = 0, int w = 0) : u(u), v(v), w(w) {}
};

int n, m, min_dist, max_dist;
vector<int> adj[N];
edge e[M];

int main() {
  scanf("%d %d %d %d", &n, &m, &min_dist, &max_dist);
  for (int i = 0; i < m; i++) {
    scanf("%d %d %d", &e[i].u, &e[i].v, &e[i].w);
    adj[e[i].u].push_back(i);
    adj[e[i].v].push_back(i);
  }

  return 0;
}