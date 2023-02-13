#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 5;
const int MOD = 998244353;

int a[N], tree[N << 2], lazy[N << 2][2];

int add(int a, int b) {
  int c = a + b;
  if (c >= MOD) c -= MOD;
  return c;
}

int mul(int a, int b) {
  return 1ll * a * b % MOD;
}

// build
void init(int u = 1, int b = 0, int e = N) {
  lazy[u][0] = 1, lazy[u][1] = -1;
  if (b == e) return void(tree[u] = a[b]);
  int mid = b + e >> 1;
  init(u << 1, b, mid), init(u << 1 | 1, mid + 1, e);
  tree[u] = add(tree[u << 1], tree[u << 1 | 1]);
}

// clear lazy value at node u
inline void push(int u, int b, int e) {
  if (lazy[u][1] != -1) {
    if (b != e) {
      lazy[u << 1][1] = lazy[u][1], lazy[u << 1 | 1][1] = lazy[u][1];
      lazy[u << 1][0] = 1, lazy[u << 1 | 1][0] = 1;
    }
    tree[u] = mul(e - b + 1, lazy[u][1]);
    lazy[u][1] = -1;
  }
  {
    if (b != e) {
      lazy[u << 1][0] = mul(lazy[u << 1][0], lazy[u][0]);
      lazy[u << 1 | 1][0] = mul(lazy[u << 1 | 1][0], lazy[u][0]);
    }
    tree[u] = mul(tree[u], lazy[u][0]);
    lazy[u][0] = 1;
  }
}

// add v on range [l, r]
void update(int l, int r, int type, int v, int u = 1, int b = 0, int e = N) {
  push(u, b, e);
  // DB();
  // debug(u, b, e, tree[u], lazy[u][0], lazy[u][1]);
  if (b > r or e < l) return;
  if (b >= l and e <= r) {
    if (type == 0) {
      lazy[u][0] = mul(lazy[u][0], 2);
    }
    else {
      lazy[u][0] = 1;
      lazy[u][1] = v;
    }
    push(u, b, e);
    // debug(u, b, e, tree[u], lazy[u][0], lazy[u][1]);
    return;
  }
  int mid = b + e >> 1;
  update(l, r, type, v, u << 1, b, mid), update(l, r, type, v, u << 1 | 1, mid + 1, e);
  tree[u] = add(tree[u << 1], tree[u << 1 | 1]);
  // debug(u, tree[u]);
}

// range [l, r] sum
int query(int l, int r, int u = 1, int b = 0, int e = N) {
  if (b > r or e < l) return 0;
  push(u, b, e);
  // debug(u, b, e, tree[u], lazy[u][0], lazy[u][1]);
  if (b >= l and e <= r) return tree[u];
  int mid = b + e >> 1;
  return add(
    query(l, r, u << 1, b, mid),
    query(l, r, u << 1 | 1, mid + 1, e)
    );
}

void test_case() {
  int n;
  cin >> n;

  vector<pair<int, int>> ranges(n);
  for (auto & [l, r] : ranges) cin >> l >> r;

  for (int i = ranges[0].first; i <= ranges[0].second; i++) a[i]++;

  init();
  // debug(query(0, N));

  for (int i = 1, p3 = 1; i < n; i++, p3 = mul(p3, 3)) {
    // DB();
    auto [l, r] = ranges[i];
    // debug(i, l, r);
    update(l, r, 1, mul(p3, 2));
    update(0, l - 1, 0, 0);
    update(r + 1, N, 0, 0);
    // debug(query(0, N));
  }

  int ans = query(0, N);

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  // cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}