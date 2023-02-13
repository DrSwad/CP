#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 2e5 + 5;
const int MOD = 1e9 + 7;

int n, k;
vector<int> e[N];
int nCk[N];
int sub[N];
int contrib;
int ans;

ll binExp(ll a, ll e, ll m = MOD) {
  if (e == -1) e = m - 2;
  ll ret = 1;
  while (e) {
    if (e & 1) ret = ret * a % m;
    a = a * a % m, e >>= 1;
  }
  return ret;
}

int add(int a, int b) {
  int ret = a + b;
  if (ret < 0) ret += MOD;
  if (ret >= MOD) ret -= MOD;
  return ret;
}

int mult(int a, int b) {
  return 1ll * a * b % MOD;
}

void init_nCk() {
  nCk[k] = 1;
  for (int i = k + 1; i < N; i++) {
    nCk[i] = mult(mult(nCk[i - 1], i), binExp(i - k, -1));
  }
}

void dfs_sub(int v, int p) {
  sub[v] = 1;
  for (int u : e[v]) {
    if (u != p) {
      dfs_sub(u, v);
      sub[v] += sub[u];
    }
  }
}

int node_contrib(int v, int p) {
  int comb = nCk[sub[v]];
  for (int u : e[v]) {
    if (u != p) {
      comb = add(comb, -nCk[sub[u]]);
    }
  }
  return mult(comb, sub[v]);
}

void init_contrib(int v, int p) {
  contrib = add(contrib, node_contrib(v, p));
  for (int u : e[v]) {
    if (u != p) {
      init_contrib(u, v);
    }
  }
}

void dfs_ans(int v, int p) {
  ans = add(ans, contrib);

  int sub_sum = 0;
  for (int u : e[v]) {
    sub_sum = add(sub_sum, nCk[sub[u]]);
  }

  contrib = add(contrib, -node_contrib(v, v));

  for (int u : e[v]) {
    if (u != p) {
      ll prev_contrib = contrib;
      contrib = add(contrib, -node_contrib(u, v));
      sub[v] = n - sub[u];
      sub[u] = n;
      contrib = add(contrib, node_contrib(u, u));
      contrib = add(contrib, mult(sub[v], add(nCk[sub[v]], add(nCk[n - sub[v]], -sub_sum))));

      dfs_ans(u, v);

      sub[u] = n - sub[v];
      sub[v] = n;
      contrib = prev_contrib;
    }
  }
  contrib = add(contrib, node_contrib(v, v));
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> k;
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    e[u].push_back(v);
    e[v].push_back(u);
  }

  init_nCk();
  dfs_sub(1, 1);
  init_contrib(1, 1);
  dfs_ans(1, 1);

  cout << ans << "\n";

  return 0;
}