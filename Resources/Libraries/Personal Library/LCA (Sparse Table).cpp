vector<int> adj[N];
int lv[N];
int par[N];
int P[LOGN][N];

void dfs(int at, int p) {
  par[at] = p;
  if (at != 0) lv[at] = lv[p] + 1;
  for (int to : adj[at]) if (to != p) dfs(to, at);
}

void initSp(int n) {
  memset(P, -1, sizeof P);
  for (int i = 0; i < n; i++) P[0][i] = par[i];
  for (int i = 1; i < LOGN; i++) {
    for (int j = 0; j < n; j++) {
      if (P[i - 1][j] != -1) {
        P[i][j] = P[i - 1][P[i - 1][j]];
      }
    }
  }
}

int lca(int u, int v) {
  if (lv[u] < lv[v]) swap(u, v);
  for (int i = LOGN - 1; i >= 0; i--) {
    if (lv[u] - (1 << i) >= lv[v]) u = P[i][u];
  }
  if (u == v) return u;
  for (int i = LOGN - 1; i >= 0; i--) {
    if (P[i][u] != P[i][v]) u = P[i][u], v = P[i][v];
  }
  return par[u];
}