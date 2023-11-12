#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz = 1e6 + 7, mod = 1e9 + 7;

int n, c[sz], beg[sz], fin[sz], dep[sz], kt;
vector<int> g[sz], col[sz];

int ex[sz << 2];
ll tree[sz << 2];

void push(int u, int b, int e) {
  if (ex[u] == -1) return;
  if (b != e) {
    int x = u << 1, y = x | 1;
    ex[x] = ex[y] = ex[u];
  }
  tree[u] = ex[u];
  ex[u] = -1;
}

void update(int l, int r, int v, int u = 1, int b = 1, int e = n) {
  if (ex[u] != -1) push(u, b, e);
  if (e<l or b> r or l > r) return;
  if (l <= b and e <= r) {
    ex[u] = v;
    return push(u, b, e);
  }
  int m = b + e >> 1, x = u << 1, y = x | 1;
  update(l, r, v, x, b, m);
  update(l, r, v, y, m + 1, e);
  tree[u] = tree[x] * tree[y] % mod;
}

ll query(int l, int r, int u = 1, int b = 1, int e = n) {
  if (ex[u] != -1) push(u, b, e);
  if (e<l or b> r or l > r) return 1;
  if (l <= b and e <= r) return tree[u];
  int m = b + e >> 1, x = u << 1, y = x | 1;
  return query(l, r, x, b, m) * query(l, r, y, m + 1, e) % mod;
}

void go(int u) {
  beg[u] = ++kt;
  for (int v : g[u]) {
    dep[v] = dep[u] + 1;
    go(v);
  }
  fin[u] = kt;
}

void solve() {
  int k;
  scanf("%d %d", &n, &k);
  for (int i = 1; i <= n; i++) g[i].clear(), col[i].clear();

  int rt;
  for (int i = 1; i <= n; i++) {
    int p;
    scanf("%d", &p);
    if (!p) rt = i;
    else g[p].push_back(i);
  }

  for (int i = 1; i <= n; i++) {
    scanf("%d", &c[i]);
    col[c[i]].push_back(i);
  }

  dep[rt] = 1;
  kt = 0;
  go(rt);

  //for(int i=1; i<=n; i++) printf("%d ", beg[i]); puts("");

  for (int i = 1; i <= k; i++) {
    auto &ara = col[i];
    sort(
      ara.begin(),
      ara.end(),
      [](int u, int v) {
        return dep[u] > dep[v];
      }
    );

    update(1, n, 1);
    for (int u : ara) {
      ll sum = 0;
      //cout << u << endl;
      for (int v : g[u]) {
        int l = beg[v], r = fin[v];
        //printf("%d = %d %d\n", v, l, r);
        sum += query(l, r);
        //printf("%lld\n", query(l, r));
        if (sum >= mod) sum -= mod;
      }
      int l = beg[u], r = fin[u];
      //cout << sum << endl;
      update(l, l, sum);
      update(l + 1, r, 1);
    }
    int ans = query(1, n);
    printf(" %d", ans);
  }
  puts("");
}

int main() {
  memset(ex, -1, sizeof(ex));
  int t, cs = 0;
  cin >> t;
  while (t--) {
    printf("Case %d:", ++cs);
    solve();
  }
}