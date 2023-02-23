#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int G;
const int MOD = 7340033;
const int N = (1 << 20) + 5;

int rev[N], w[N], inv_n;

int bigMod(int a, int e, int mod) {
  if (e == -1) e = mod - 2;
  int ret = 1;
  while (e) {
    if (e & 1) ret = (ll) ret * a % mod;
    a = (ll) a * a % mod; e >>= 1;
  }
  return ret;
}

void prepare(int &n) {
  int sz = abs(31 - __builtin_clz(n));
  int r = bigMod(G, (MOD - 1) / n, MOD);
  inv_n = bigMod(n, MOD - 2, MOD), w[0] = w[n] = 1;
  for (int i = 1; i < n; ++i) w[i] = (ll) w[i - 1] * r % MOD;
  for (int i = 1; i < n; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (sz - 1));
}

void ntt(int *a, int n, int dir) {
  for (int i = 1; i < n - 1; ++i) {
    if (i < rev[i]) swap(a[i], a[rev[i]]);
  }
  for (int m = 2; m <= n; m <<= 1) {
    for (int i = 0; i < n; i += m) {
      for (int j = 0; j < (m >> 1); ++j) {
        int &u = a[i + j], &v = a[i + j + (m >> 1)];
        int t = (ll) v * w[dir ? n - n / m * j : n / m * j] % MOD;
        v = u - t < 0 ? u - t + MOD : u - t;
        u = u + t >= MOD ? u + t - MOD : u + t;
      }
    }
  } if (dir) for (int i = 0; i < n; ++i) a[i] = (ll) a[i] * inv_n % MOD;
}

int f_a[N], f_b[N];

vector<int> multiply(vector<int> a, vector<int> b) {
  int sz = 1, n = a.size(), m = b.size();
  while (sz < n + m - 1) sz <<= 1; prepare(sz);
  for (int i = 0; i < sz; ++i) f_a[i] = i < n ? a[i] : 0;
  for (int i = 0; i < sz; ++i) f_b[i] = i < m ? b[i] : 0;
  ntt(f_a, sz, 0); ntt(f_b, sz, 0);
  for (int i = 0; i < sz; ++i) f_a[i] = (ll) f_a[i] * f_b[i] % MOD;
  ntt(f_a, sz, 1); return vector<int>(f_a, f_a + n + m - 1);
}

int primitive_root(int p) {
  vector<int> factor;
  int tmp = p - 1;
  for (int i = 2; i * i <= tmp; ++i) {
    if (tmp % i == 0) {
      factor.emplace_back(i);
      while (tmp % i == 0) tmp /= i;
    }
  }
  if (tmp != 1) factor.emplace_back(tmp);
  for (int root = 1; ; ++root) {
    bool flag = true;
    for (int i = 0; i < (int) factor.size(); ++i) {
      if (bigMod(root, (p - 1) / factor[i], p) == 1) {
        flag = false; break;
      }
    }
    if (flag) return root;
  }
}

ll inv[N], fact[N], ifact[N];

void init() {
  inv[1] = fact[0] = ifact[0] = 1;
  for (int i = 2; i < N; i++) inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
  for (int i = 1; i < N; i++) fact[i] = fact[i - 1] * i % MOD;
  for (int i = 1; i < N; i++) ifact[i] = ifact[i - 1] * inv[i] % MOD;

  G = primitive_root(MOD);
}

ll nCk(int n, int k) {
  if (k<0 or k> n) return 0;
  return fact[n] * ifact[k] % MOD * ifact[n - k] % MOD;
}

void test_case() {
  int n;
  cin >> n;

  vector<int> cnt(4, 0);
  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    int id = (x < 0) * 2 + (y < 0);
    cnt[id]++;
  }

  vector<int> a(n + 1), b(n + 1);
  for (int i = 0; i <= n; i++) {
    a[i] = nCk(cnt[0], i) * nCk(cnt[3], i) % MOD;
    b[i] = nCk(cnt[1], i) * nCk(cnt[2], i) % MOD;
  }

  vector<int> c = multiply(a, b);
  for (int i = 1; i <= n; i++) {
    if (i > 1) cout << " ";
    if (i % 2 == 1 or i / 2 >= c.size()) cout << "0";
    else cout << c[i / 2];
  }
  cout << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  init();

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case " << cs << ":\n";
    test_case();
  }

  return 0;
}