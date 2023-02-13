#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld; // USE DOUBLE, MUCH FASTER AND ALMOST ALWAYS WORKS

struct cplx {
  ld a, b;

  cplx(ld a = 0, ld b = 0) : a(a), b(b) {}

  const cplx operator +(const cplx &c) const {
    return cplx(a + c.a, b + c.b);
  }

  const cplx operator -(const cplx &c) const {
    return cplx(a - c.a, b - c.b);
  }

  const cplx operator *(const cplx &c) const {
    return cplx(a * c.a - b * c.b, a * c.b + b * c.a);
  }

  const cplx conj() const {
    return cplx(a, -b);
  }
};

const ld PI = acosl(-1);
const int MOD = 1e9 + 7;
const int N = (1 << 20) + 5;

int rev[N]; cplx w[N];

void prepare(int n) {
  int sz = __builtin_ctz(n);
  for (int i = 1; i < n; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (sz - 1));
  w[0] = 0, w[1] = 1, sz = 1;
  while (1 << sz < n) {
    ld ang = 2 * PI / (1 << (sz + 1));
    cplx w_n = cplx(cosl(ang), sinl(ang));
    for (int i = 1 << (sz - 1); i < (1 << sz); ++i) {
      w[i << 1] = w[i], w[i << 1 | 1] = w[i] * w_n;
    } ++sz;
  }
}

void fft(cplx *a, int n) {
  for (int i = 1; i < n - 1; ++i) {
    if (i < rev[i]) swap(a[i], a[rev[i]]);
  }
  for (int h = 1; h < n; h <<= 1) {
    for (int s = 0; s < n; s += h << 1) {
      for (int i = 0; i < h; ++i) {
        cplx &u = a[s + i], &v = a[s + i + h], t = v * w[h + i];
        v = u - t, u = u + t;
      }
    }
  }
}

static cplx f[N], g[N], u[N], v[N];

vector<int> multiply(vector<int> &a, vector<int> &b) {
  int n = a.size(), m = b.size();
  int sz = n + m - 1;
  while (sz & (sz - 1)) sz = (sz | (sz - 1)) + 1;
  prepare(sz);
  for (int i = 0; i < sz; ++i) f[i] = cplx(i < n ? a[i] : 0, i < m ? b[i] : 0);
  fft(f, sz);
  for (int i = 0; i <= (sz >> 1); ++i) {
    int j = (sz - i) & (sz - 1);
    cplx x = (f[i] * f[i] - (f[j] * f[j]).conj()) * cplx(0, -0.25);
    f[j] = x, f[i] = x.conj();
  }
  fft(f, sz);
  vector<int> c(sz);
  for (int i = 0; i < sz; ++i) c[i] = f[i].a / sz + 0.5;
  return c;
}

vector<int> multiplyMod(vector<int> &a, vector<int> &b) {
  int n = a.size(), m = b.size();
  int sz = 1;
  while (sz < n + m - 1) sz <<= 1;
  prepare(sz);
  for (int i = 0; i < sz; ++i) {
    f[i] = i < n ? cplx(a[i] & 32767, a[i] >> 15) : cplx(0, 0);
    g[i] = i < m ? cplx(b[i] & 32767, b[i] >> 15) : cplx(0, 0);
  }
  fft(f, sz), fft(g, sz);
  for (int i = 0; i < sz; ++i) {
    int j = (sz - i) & (sz - 1);
    static cplx da, db, dc, dd;
    da = (f[i] + f[j].conj()) * cplx(0.5, 0);
    db = (f[i] - f[j].conj()) * cplx(0, -0.5);
    dc = (g[i] + g[j].conj()) * cplx(0.5, 0);
    dd = (g[i] - g[j].conj()) * cplx(0, -0.5);
    u[j] = da * dc + da * dd * cplx(0, 1);
    v[j] = db * dc + db * dd * cplx(0, 1);
  }
  fft(u, sz), fft(v, sz);
  vector<int> c(sz);
  for (int i = 0; i < sz; ++i) {
    int da = (ll) (u[i].a / sz + 0.5) % MOD;
    int db = (ll) (u[i].b / sz + 0.5) % MOD;
    int dc = (ll) (v[i].a / sz + 0.5) % MOD;
    int dd = (ll) (v[i].b / sz + 0.5) % MOD;
    c[i] = (da + ((ll) (db + dc) << 15) + ((ll) dd << 30)) % MOD;
  }
  return c;
}

const int mod = 1e9 + 7;
int add(int a, int b) {
  int c = a + b;
  return c < mod ? c : c - mod;
}
int mul(int a, int b) {
  return 1ll * a * b % mod;
}

void test_case() {
  int n, m, k;
  cin >> n >> m >> k;

  vector<int> p3(1 + m + k);
  p3[0] = 1;
  for (int i = 1; i <= m + k; i++) {
    p3[i] = mul(p3[i - 1], 3);
  }

  int tot = n + m + k;
  vector<int> fact(tot), inv(tot), ifact(tot);
  inv[1] = fact[0] = ifact[0] = 1;
  for (int i = 2; i < tot; i++) inv[i] = mul(inv[mod % i], mod - mod / i);
  for (int i = 1; i < tot; i++) fact[i] = mul(fact[i - 1], i);
  for (int i = 1; i < tot; i++) ifact[i] = mul(ifact[i - 1], inv[i]);

  vector<int> poly0(1 + m), poly1(1 + k);
  for (int i = 0; i <= m; i++) poly0[i] = ifact[i];
  for (int i = 0; i <= k; i++) poly1[i] = ifact[i];
  vector<int> poly2 = multiplyMod(poly0, poly1);
  for (int i = 0; i <= m + k; i++) poly2[i] = mul(poly2[i], fact[i]);

  int ans = 0;
  for (int take = 0; take <= m + k; take++) {
    int placement = mul(fact[n + take - 1], mul(ifact[n - 1], ifact[take]));
    ans = add(ans, mul(placement, mul(poly2[take], p3[m + k - take])));
  }

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