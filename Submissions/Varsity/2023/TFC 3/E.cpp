#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 9, LG = 18, inf = 1e9 + 9;

int n;
int f[N];
void bit_update(int p, int v) {
  while (p <= n) f[p] += v, p += p & -p;
}
int bit_pref(int p) {
  int ret = 0;
  while (p) ret += f[p], p -= p & -p;
  return ret;
}
int bit_range(int l, int r) {
  return bit_pref(r) - bit_pref(l - 1);
}

int lazy[N << 2];
pair<int, int> tree[N << 2];

// build
void st_init(int u = 1, int b = 1, int e = n) {
  lazy[u] = 0; // modify
  if (b == e) return void(tree[u] = {0, b});
  int mid = b + e >> 1;
  st_init(u << 1, b, mid), st_init(u << 1 | 1, mid + 1, e);
  tree[u] = min(tree[u << 1], tree[u << 1 | 1]); // modify
}

// clear lazy value at node u
inline void st_push(int u, int b, int e) {
  tree[u].first += lazy[u];                                               // modify
  if (b != e) lazy[u << 1] += lazy[u], lazy[u << 1 | 1] += lazy[u]; // modify
  lazy[u] = 0;                                                      // modify
}

// add v on range [l, r]
void st_update(int l, int r, int v, int u = 1, int b = 1, int e = n) {
  if (lazy[u]) st_push(u, b, e); // modify
  if (b > r or e < l) return;
  if (b >= l and e <= r) {
    lazy[u] += v; // modify
    return st_push(u, b, e);
  }
  int mid = b + e >> 1;
  st_update(l, r, v, u << 1, b, mid), st_update(l, r, v, u << 1 | 1, mid + 1, e);
  tree[u] = min(tree[u << 1], tree[u << 1 | 1]); // modify
}

// range [l, r] sum
pair<int, int> st_query(int l, int r, int u = 1, int b = 1, int e = n) {
  if (b > r or e < l) return {inf, -1}; // modify
  if (lazy[u]) st_push(u, b, e); // modify
  if (b >= l and e <= r) return tree[u];
  int mid = b + e >> 1;
  return min(
    st_query(l, r, u << 1, b, mid),
    st_query(l, r, u << 1 | 1, mid + 1, e)
  );                                        // modify
}

vector<int> g[N];
int par[N][LG + 1], dep[N], sz[N];
void dfs(int u, int p = 0) {
  par[u][0] = p;
  dep[u] = dep[p] + 1;
  sz[u] = 1;
  for (int i = 1; i <= LG; i++) par[u][i] = par[par[u][i - 1]][i - 1];
  if (p) g[u].erase(find(g[u].begin(), g[u].end(), p));
  for (auto &v : g[u]) if (v != p) {
      dfs(v, u);
      sz[u] += sz[v];
      if (sz[v] > sz[g[u][0]]) swap(v, g[u][0]);
    }
}
int lca(int u, int v) {
  if (dep[u] < dep[v]) swap(u, v);
  for (int k = LG; k >= 0; k--) if (dep[par[u][k]] >= dep[v]) u = par[u][k];
  if (u == v) return u;
  for (int k = LG; k >= 0; k--) if (par[u][k] != par[v][k]) u = par[u][k], v = par[v][k];
  return par[u][0];
}
int kth(int u, int k) {
  assert(k >= 0);
  for (int i = 0; i <= LG; i++) if (k & (1 << i)) u = par[u][i];
  return u;
}
int T, head[N], st[N], en[N];
void dfs_hld(int u) {
  st[u] = ++T;
  for (auto v : g[u]) {
    head[v] = (v == g[u][0] ? head[u] : v);
    dfs_hld(v);
  }
  en[u] = T;
}
void update_up(int u, int v, int w) {
  // debug("update_up", u, v, w);
  while (head[u] != head[v]) {
    // debug(u);
    {
      auto [val, index] = st_query(st[head[u]], st[u]);
      while (val <= w) {
        bit_update(index, 1);
        st_update(index, index, inf);

        auto [nval, nindex] = st_query(st[head[u]], st[u]);
        val = nval;
        index = nindex;
      }
      st_update(st[head[u]], st[u], -w);
    }
    u = par[head[u]][0];
  }
  auto [val, index] = st_query(st[v], st[u]);
  while (val <= w) {
    assert(index);
    bit_update(index, 1);
    st_update(index, index, inf);

    auto [nval, nindex] = st_query(st[v], st[u]);
    val = nval;
    index = nindex;
  }
  st_update(st[v], st[u], -w);
}
void update(int u, int v, int w) {
  // debug(u, v, w);
  int l = lca(u, v);
  update_up(u, l, w);
  if (v != l) update_up(v, kth(v, dep[v] - dep[l] - 1), w);
}
int query_up(int u, int v) {
  // debug("query_up", u, v);
  int ans = 0;
  while (head[u] != head[v]) {
    ans += bit_range(st[head[u]], st[u]);
    u = par[head[u]][0];
  }
  ans += bit_range(st[v], st[u]);
  return ans;
}
int query(int u, int v) {
  // debug(u, v);
  int l = lca(u, v);
  int ans = query_up(u, l);
  if (v != l) ans += query_up(v, kth(v, dep[v] - dep[l] - 1));
  return ans;
}

void test_case() {
  // cin >> n;
  // for (int i = 1; i < n; i++) {
  //   int u, v;
  //   cin >> u >> v;
  //   g[u].push_back(v);
  //   g[v].push_back(u);
  // }

  // dfs(1);
  // head[1] = 1;
  // dfs_hld(1);

  // int q;
  // cin >> q;
  // t.build(1, 1, n);

  // while (q--) {
  //   string ty;
  //   int u, v;
  //   cin >> ty >> u >> v;
  //   if (ty == "add") {
  //     t.upd(1, 1, n, st[u], en[u], v);
  //   } else {
  //     cout << query(u, v) << '\n';
  //   }
  // }

  int q;
  cin >> n >> q;

  int a, b;
  cin >> a >> b;

  vector<int> c(n + 1);
  for (int i = 1; i <= n; i++) cin >> c[i];

  vector<int> min_w(n + 1);
  for (int i = 1; i <= n; i++) {
    long long cur = 1ll * a * c[i] + b;
    if (cur >= 0) min_w[i] = 0;
    else {
      cur = -cur;
      if (a == 0) min_w[i] = inf;
      else min_w[i] = min((long long)inf, (cur + a - 1) / a);
    }
  }

  for (int i = 1; i <= n; i++) g[i].clear();

  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  dfs(1);
  head[1] = 1;
  T = 0;
  dfs_hld(1);

  st_init();
  fill(f, f + n + 1, 0);
  for (int i = 1; i <= n; i++) {
    if (min_w[i] == 0) {
      bit_update(st[i], 1);
      st_update(st[i], st[i], inf);
    }
    else st_update(st[i], st[i], min_w[i]);
  }

  while (q--) {
    int type;
    cin >> type;

    if (type == 1) {
      int u, v, w;
      cin >> u >> v >> w;
      update(u, v, w);
    }
    else {
      int u, v;
      cin >> u >> v;
      cout << query(u, v) << "\n";
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}