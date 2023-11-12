#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
const int N = 4e5 + 5;
const int A = 300;
const int mod = 1e9 + 7;

int add(int a, int b) {
  int c = a + b;
  return c < mod ? c : c - mod;
}

int mul(int a, int b) {
  return 1ll * a * b % mod;
}

int binExp(int a, int e) {
  if (e < 0) e = (mod - 1) + e;
  int ret = 1;
  while (e) {
    if (e & 1) ret = mul(ret, a);
    a = mul(a, a), e >>= 1;
  }
  return ret;
}

int n;
int a[N];
ull tree_or[N << 2], lazy_or[N << 2];
int tree_mul[N << 2], lazy_mul[N << 2];
vector<int> primes;

// build
void init(int u = 1, int b = 1, int e = n) {
  lazy_or[u] = 0;
  lazy_mul[u] = 1;
  if (b == e) {
    for (int i = 0; i < primes.size(); i++) {
      if (a[b] % primes[i] == 0) {
        tree_or[u] |= 1ull << i;
      }
    }
    tree_mul[u] = a[b];
    return;
  }
  int mid = b + e >> 1;
  init(u << 1, b, mid), init(u << 1 | 1, mid + 1, e);
  tree_or[u] = tree_or[u << 1] | tree_or[u << 1 | 1];
  tree_mul[u] = mul(tree_mul[u << 1], tree_mul[u << 1 | 1]);
}

// clear lazy value at node u
inline void push(int u, int b, int e) {
  tree_or[u] |= lazy_or[u];
  if (lazy_mul[u] != 1) tree_mul[u] = mul(tree_mul[u], binExp(lazy_mul[u], e - b + 1));
  if (b != e) {
    lazy_or[u << 1] |= lazy_or[u];
    lazy_or[u << 1 | 1] |= lazy_or[u];
    lazy_mul[u << 1] = mul(lazy_mul[u << 1], lazy_mul[u]);
    lazy_mul[u << 1 | 1] = mul(lazy_mul[u << 1 | 1], lazy_mul[u]);
  }
  lazy_or[u] = 0;
  lazy_mul[u] = 1;
}

// add v on range [l, r]
void update(int l, int r, ull v_or, int v_mul, int u = 1, int b = 1, int e = n) {
  if (lazy_or[u] != 0 or lazy_mul[u] != 1) push(u, b, e);
  if (b > r or e < l) return;
  if (b >= l and e <= r) {
    lazy_or[u] |= v_or;
    lazy_mul[u] = mul(lazy_mul[u], v_mul);
    return push(u, b, e);
  }
  int mid = b + e >> 1;
  update(l, r, v_or, v_mul, u << 1, b, mid), update(l, r, v_or, v_mul, u << 1 | 1, mid + 1, e);
  tree_or[u] = tree_or[u << 1] | tree_or[u << 1 | 1];
  tree_mul[u] = mul(tree_mul[u << 1], tree_mul[u << 1 | 1]);
}

// range [l, r] sum
pair<ull, int> query(int l, int r, int u = 1, int b = 1, int e = n) {
  if (b > r or e < l) return {0ull, 1};
  if (lazy_or[u] != 0 or lazy_mul[u] != 1) push(u, b, e);
  if (b >= l and e <= r) return {tree_or[u], tree_mul[u]};
  int mid = b + e >> 1;
  auto [l_or, l_mul] = query(l, r, u << 1, b, mid);
  auto [r_or, r_mul] = query(l, r, u << 1 | 1, mid + 1, e);
  return {l_or | r_or, mul(l_mul, r_mul)};
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  {
    vector<bool> is_prime(A + 1, true);
    for (int p = 2; p <= A; p++) {
      if (is_prime[p]) {
        primes.push_back(p);
        for (int q = 2 * p; q <= A; q += p) {
          is_prime[q] = false;
        }
      }
    }
    assert(primes.size() <= 64);
  }

  int q;
  cin >> n >> q;
  for (int i = 1; i <= n; i++) cin >> a[i];

  init();

  while (q--) {
    string type;
    cin >> type;

    if (type == "MULTIPLY") {
      int l, r, x_mul;
      cin >> l >> r >> x_mul;

      ull x_or = 0;
      for (int i = 0; i < primes.size(); i++) {
        if (x_mul % primes[i] == 0) {
          x_or |= 1ull << i;
        }
      }

      update(l, r, x_or, x_mul);
    }
    else {
      int l, r;
      cin >> l >> r;

      auto [q_or, q_mul] = query(l, r);

      int phi = q_mul;
      for (int i = 0; i < primes.size(); i++) {
        if (q_or >> i & 1) {
          phi = mul(phi, mul(primes[i] - 1, binExp(primes[i], -1)));
        }
      }

      cout << phi << "\n";
    }
  }

  return 0;
}