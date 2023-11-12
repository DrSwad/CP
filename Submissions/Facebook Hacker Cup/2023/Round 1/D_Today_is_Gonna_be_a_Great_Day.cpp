#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
const int N = 1e6 + 10;
int n, a[N], lazy[N << 2];
pair<int, int> tree[N << 2][2];

void pull(int u, int b, int e) {
  tree[u][0] = min(tree[u << 1][0], tree[u << 1 | 1][0]);
  tree[u][1] = max(tree[u << 1][1], tree[u << 1 | 1][1]);
}

// build
void init(int u = 1, int b = 1, int e = n) {
  lazy[u] = 1;
  if (b == e) return void(tree[u][0] = tree[u][1] = {a[b], -b});
  int mid = b + e >> 1;
  init(u << 1, b, mid), init(u << 1 | 1, mid + 1, e);
  pull(u, b, e);
}

// clear lazy value at node u
inline void push(int u, int b, int e) {
  if (lazy[u] != 1) {
    if (tree[u][0].first != tree[u][1].first) {
      swap(tree[u][0], tree[u][1]);
    }
    tree[u][0].first = mod - tree[u][0].first;
    tree[u][1].first = mod - tree[u][1].first;
  }
  if (b != e) lazy[u << 1] *= lazy[u], lazy[u << 1 | 1] *= lazy[u];
  lazy[u] = 1;
}

// multiply v on range [l, r]
void update(int l, int r, int v, int u = 1, int b = 1, int e = n) {
  if (lazy[u] != 1) push(u, b, e);
  if (b > r or e < l) return;
  if (b >= l and e <= r) {
    lazy[u] *= v;
    return push(u, b, e);
  }
  int mid = b + e >> 1;
  update(l, r, v, u << 1, b, mid), update(l, r, v, u << 1 | 1, mid + 1, e);
  pull(u, b, e);
}

// range [l, r] max
pair<int, int> query(int l, int r, int u = 1, int b = 1, int e = n) {
  if (b > r or e < l) return {INT_MIN, INT_MIN};
  if (lazy[u]) push(u, b, e);
  if (b >= l and e <= r) return tree[u][1];
  int mid = b + e >> 1;
  return max(
    query(l, r, u << 1, b, mid),
    query(l, r, u << 1 | 1, mid + 1, e)
  );
}

void test_case() {
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];

  init();

  int q;
  cin >> q;

  long long ans = 0;

  while (q--) {
    int l, r;
    cin >> l >> r;
    update(l, r, -1);
    ans += -query(1, n).second;
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}