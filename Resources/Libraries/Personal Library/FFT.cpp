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