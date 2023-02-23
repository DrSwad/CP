#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef complex<double> base;
const double PI = acos(-1);

void fft(vector<base> &a, bool inv) {
  int n = a.size();
  int j = 0;

  for (int i = 1; i < n; i++) {
    int bit = n >> 1;

    while (j >= bit) {
      j -= bit;
      bit >>= 1;
    }
    j += bit;

    if (i < j) swap(a[i], a[j]);
  }

  vector<base> roots(n / 2);
  double ang = 2 * PI / n * (inv ? -1 : 1);
  for (int i = 0; i < n / 2; i++) roots[i] = base(cos(ang * i), sin(ang * i));

  for (int i = 2; i <= n; i <<= 1) {
    int step = n / i;

    for (int j = 0; j < n; j += i) {
      for (int k = 0; k < i / 2; k++) {
        base u = a[j + k], v = a[j + k + i / 2] * roots[k * step];
        a[j + k] = u + v;
        a[j + k + i / 2] = u - v;
      }
    }
  }

  if (inv) for (int i = 0; i < n; i++) a[i] /= n;
}

vector<ll> multiply(vector<ll> &a, vector<ll> &b) {
  vector<base> fa(a.begin(), a.end()), fb(b.begin(), b.end());

  int n = 2;
  while (n < a.size() + b.size()) n <<= 1;

  fa.resize(n);
  fft(fa, false);

  fb.resize(n);
  fft(fb, false);

  for (int i = 0; i < n; i++) fa[i] *= fb[i];

  fft(fa, 1);
  vector<ll> ret(n);
  for (int i = 0; i < n; i++) ret[i] = (ll)round(fa[i].real());

  return ret;
}

const int N = 1e6 + 3;
const int MOD = 1e6 + 3;

int mul(int a, int b) {
  return (ll)a * b % MOD;
}

int add(int a, int b) {
  int c = a + b;
  return c < MOD ? c : c - MOD;
}

ll binExp(ll a, ll e, ll m = MOD) {
  if (e == -1) e = m - 2; ll ret = 1;
  while (e) {
    if (e & 1) ret = ret * a % m;
    a = a * a % m, e >>= 1;
  }
  return ret;
}

int fact[N], ifact[N];

void init() {
  fact[0] = 1;
  for (int i = 1; i < N; i++) fact[i] = mul(fact[i - 1], i);
  ifact[N - 1] = binExp(fact[N - 1], -1);
  for (int i = N - 2; i >= 0; i--) {
    ifact[i] = mul(ifact[i + 1], i + 1);
  }
}

int nCk(int n, int k) {
  if (k<0 or k> n) return 0;
  return mul(fact[n], mul(ifact[k], ifact[n - k]));
}

void test_case() {
  int n, k, r;
  cin >> n >> k >> r;

  if (k > n) {
    cout << "0\n";
    return;
  }

  vector<int> freq(r, 0);
  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;
    freq[a % r]++;
  }

  // debug(freq);

  vector<vector<int>> dp(r, vector<int>(k + 1, 0));
  dp[0][0] = 1;

  for (int curr_rem = 0; curr_rem < r; curr_rem++) {
    // DB();
    // debug(curr_rem);
    vector<vector<int>> curr_poly(r, vector<int>(k + 1, 0));
    for (int curr_take = 0; curr_take <= k; curr_take++) {
      int rem = (curr_take * curr_rem) % r;
      curr_poly[rem][curr_take] = nCk(freq[curr_rem], curr_take);
    }

    vector<vector<int>> ndp(r, vector<int>(k + 1, 0));

    for (int rem = 0; rem < r; rem++) {
      for (int prev_rem = 0; prev_rem < r; prev_rem++) {
        vector<ll> poly1;
        for (int i : curr_poly[rem]) poly1.push_back(i);
        vector<ll> poly2;
        for (int i : dp[prev_rem]) poly2.push_back(i);

        vector<ll> got = multiply(poly1, poly2);
        for (ll &i : got) i %= MOD;

        int new_rem = (prev_rem + rem) % r;
        for (int take = 0; take <= k; take++) {
          ndp[new_rem][take] = add(ndp[new_rem][take], got[take]);
        }
        // debug(rem, prev_rem, ndp);
      }
    }
    swap(dp, ndp);
    // debug(dp);
  }

  cout << dp[0][k] << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  init();

  int t = 1;
  // cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}