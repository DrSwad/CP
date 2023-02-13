#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e5 + 5;
const int MOD = 1e9 + 7;

int n;
vector<pair<int, ll>> row[N];
int p[N], sz[N];
vector<pair<int, ll>> e[N];
ll d[N];

int root(int node) {
  if (p[node] == node) return node;
  return p[node] = root(p[node]);
}

void merge(int cu, int cv, ll w) {
  int ru = root(cu);
  int rv = root(cv);
  if (ru == rv) return;

  if (sz[ru] > sz[rv]) swap(ru, rv);
  p[rv] = ru;
  sz[ru] += sz[rv];

  e[cu].emplace_back(cv, w);
  e[cv].emplace_back(cu, (MOD - w) % MOD);
}

void dfs(int at, int from) {
  for (auto it = e[at].begin(); it != e[at].end(); it++) {
    int to = it->first;
    ll w = it->second;
    if (to == from) continue;
    d[to] = (d[at] + w) % MOD;
    dfs(to, at);
  }
}

int main() {
  int E;
  scanf("%d %d", &n, &E);

  while (E--) {
    int u, v, w;
    scanf("%d %d %d", &u, &v, &w);
    v -= n;
    w %= MOD;
    row[u].emplace_back(v, w);
  }

  iota(begin(p), end(p), 0);

  for (int u = 1; u <= n; u++) {
    if (row[u].empty()) continue;
    int v0 = row[u].begin()->first;
    ll w0 = row[u].begin()->second;
    for (auto it = row[u].begin() + 1; it != row[u].end(); it++) {
      int v = it->first;
      ll w = it->second;
      merge(v0, v, w - w0);
    }
  }

  for (int v = 2; v <= n; v++) assert(root(v) == root(1));

  dfs(1, 0);

  ll base_sum = 0, base_sq = 0;
  for (int v = 1; v <= n; v++) {
    (base_sum += d[v]) %= MOD;
    (base_sq += d[v] * d[v] % MOD) %= MOD;
  }

  ll ans = 0;
  for (int u = 1; u <= n; u++) {
    if (row[u].empty()) continue;
    int v = row[u].begin()->first;
    ll w = row[u].begin()->second;
    ll D = (w - d[v] + MOD) % MOD;
    (ans += (base_sq + 2ll * D * base_sum + D * D % MOD * n % MOD) % MOD) %= MOD;
  }

  cout << ans << endl;

  return 0;
}