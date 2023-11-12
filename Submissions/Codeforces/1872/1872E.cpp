#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int n, a[N], tree[N << 2][2], lazy[N << 2];
char s[N];

inline void pull(int u) {
  tree[u][0] = tree[u << 1][0] ^ tree[u << 1 | 1][0];
  tree[u][1] = tree[u << 1][1] ^ tree[u << 1 | 1][1];
}

// build
void init(int u = 1, int b = 1, int e = n) {
  lazy[u] = 0;
  if (b == e) {
    if (s[b] == '1') tree[u][0] = 0, tree[u][1] = a[b];
    else tree[u][0] = a[b], tree[u][1] = 0;
    return;
  }
  int mid = b + e >> 1;
  init(u << 1, b, mid), init(u << 1 | 1, mid + 1, e);
  pull(u);
}

// clear lazy value at node u
inline void push(int u, int b, int e) {
  if (lazy[u]) swap(tree[u][0], tree[u][1]);
  if (b != e) lazy[u << 1] ^= lazy[u], lazy[u << 1 | 1] ^= lazy[u];
  lazy[u] = 0;
}

// add v on range [l, r]
void update(int l, int r, int v, int u = 1, int b = 1, int e = n) {
  if (lazy[u]) push(u, b, e);
  if (b > r or e < l) return;
  if (b >= l and e <= r) {
    lazy[u] ^= v;
    return push(u, b, e);
  }
  int mid = b + e >> 1;
  update(l, r, v, u << 1, b, mid), update(l, r, v, u << 1 | 1, mid + 1, e);
  pull(u);
}

// range [l, r] sum
int query(int l, int r, int v, int u = 1, int b = 1, int e = n) {
  if (b > r or e < l) return 0;
  if (lazy[u]) push(u, b, e);
  if (b >= l and e <= r) return tree[u][v];
  int mid = b + e >> 1;
  return query(l, r, v, u << 1, b, mid) ^ query(l, r, v, u << 1 | 1, mid + 1, e);
}

void test_case() {
  cin >> n;

  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }

  for (int i = 1; i <= n; i++) {
    cin >> s[i];
  }

  init();

  int q;
  cin >> q;

  bool first_output = true;
  while (q--) {
    int type;
    cin >> type;

    if (type == 1) {
      int l, r;
      cin >> l >> r;
      update(l, r, 1);
    }
    else {
      int v;
      cin >> v;
      if (!first_output) cout << " ";
      first_output = false;
      cout << query(1, n, v);
    }
  }
  cout << "\n";
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