// Range Minimum Query

const int N = 500010;

// 0-indexed, point updates, commutative merge
namespace Special {
int n, a[N], tree[N << 1];

// build
void init() {
  for (int i = 0; i < n; ++i) { tree[n + i] = a[i]; }
  for (int i = n - 1; i >= 0; --i) {
    tree[i] = min(tree[i << 1], tree[i << 1 | 1]);         // modify
  }
}

// assign a[p] = v
void update(int p, int v) {
  for (tree[p += n] = v; p > 1; p >>= 1) {
    tree[p >> 1] = min(tree[p], tree[p ^ 1]);         // modify
  }
}

// range [l, r) sum
int query(int l, int r) {
  int ret = INT_MAX;       // modify
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) ret = min(ret, tree[l++]);         // modify
    if (r & 1) ret = min(ret, tree[--r]);         // modify
  }
  return ret;
}
}

// 1-indexed, range updates, no restriction on merge
namespace General {
int n, a[N], tree[N << 2], lazy[N << 2];

// build
void init(int u = 1, int b = 1, int e = n) {
  lazy[u] = 0;       // modify
  if (b == e) return void(tree[u] = a[b]);
  int mid = b + e >> 1;
  init(u << 1, b, mid), init(u << 1 | 1, mid + 1, e);
  tree[u] = min(tree[u << 1], tree[u << 1 | 1]);       // modify
}

// clear lazy value at node u
inline void push(int u, int b, int e) {
  tree[u] += lazy[u];       // modify
  if (b != e) lazy[u << 1] += lazy[u], lazy[u << 1 | 1] += lazy[u];       // modify
  lazy[u] = 0;       // modify
}

// add v on range [l, r]
void update(int l, int r, int v, int u = 1, int b = 1, int e = n) {
  if (lazy[u]) push(u, b, e);
  if (b > r or e < l) return;
  if (b >= l and e <= r) {
    lazy[u] += v;         // modify
    return push(u, b, e);
  }
  int mid = b + e >> 1;
  update(l, r, v, u << 1, b, mid), update(l, r, v, u << 1 | 1, mid + 1, e);
  tree[u] = min(tree[u << 1], tree[u << 1 | 1]);       // modify
}

// range [l, r] sum
int query(int l, int r, int u = 1, int b = 1, int e = n) {
  if (b > r or e < l) return INT_MAX;       // modify
  if (lazy[u]) push(u, b, e);
  if (b >= l and e <= r) return tree[u];
  int mid = b + e >> 1;
  return min(query(l, r, u << 1, b, mid), query(l, r, u << 1 | 1, mid + 1, e));       // modify
}

// index of the rightmost zero
int lastZero(int u = 1, int b = 1, int e = n) {
  if (b == e) return b;
  if (lazy[u]) push(u, b, e);
  int mid = b + e >> 1;
  if (lazy[u << 1 | 1]) push(u << 1 | 1, mid + 1, e);
  if (tree[u << 1 | 1]) return lastZero(u << 1, b, mid);
  return lastZero(u << 1 | 1, mid + 1, e);
}
}