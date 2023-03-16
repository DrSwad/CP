#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e5 + 5;
const int LOGN = 18;

int n, m, s, q;
vector<tuple<int, int, int>> adj[N];
int lv[N];
int P[LOGN][N];
ll cost[2][LOGN][N];

void dfs(int at, int p) {
  P[0][at] = p;
  if (at != 0) lv[at] = lv[p] + 1;
  for (auto [to, w, iw] : adj[at]) {
    if (to != p) {
      cost[0][0][to] = iw;
      cost[1][0][to] = w;
      dfs(to, at);
    }
  }
}

void initSp() {
  memset(P, -1, sizeof P);
  dfs(0, -1);
  for (int i = 1; i < LOGN; i++) {
    for (int j = 0; j < n; j++) {
      if (P[i - 1][j] != -1) {
        P[i][j] = P[i - 1][P[i - 1][j]];
        cost[0][i][j] = cost[0][i - 1][P[i - 1][j]] + cost[0][i - 1][j];
        cost[1][i][j] = cost[1][i - 1][P[i - 1][j]] + cost[1][i - 1][j];
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
  return P[0][u];
}

ll go(int u, int v, int type) {
  assert (lv[u] >= lv[v]);
  ll ret = 0;
  for (int i = LOGN - 1; i >= 0; i--) {
    if (lv[u] - (1 << i) >= lv[v]) ret += cost[type][i][u], u = P[i][u];
  }
  assert(u == v);
  return ret;
}

void reset() {
  for (int i = 0; i < n; i++) adj[i].clear(); 
}

void test_case() {
  cin >> n >> m >> s >> q;
  assert(m == n - 1);

  while (m--) {
    int x, y, w, iw;
    cin >> x >> y >> w >> iw;
    x--, y--;
    adj[x].emplace_back(y, w, iw);
    adj[y].emplace_back(x, iw, w);
  }

  initSp();

  int min_s = INT_MAX;
  while (s--) {
    int t;
    cin >> t;
    min_s = min(min_s, t);
  }

  while (q--) {
    int a, b;
    cin >> a >> b;
    a--, b--;

    int l = lca(a, b);
    ll ans = go(a, l, 0) + go(b, l, 1);
    ans = min(ans, (ll)min_s);

    cout << ans << "\n";
  }

  reset();
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
