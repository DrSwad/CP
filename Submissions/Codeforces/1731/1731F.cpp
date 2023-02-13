#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 998244353;
const int N = 51;

int fact[N], ifact[N];

ll binExp(ll a, ll e, ll m = MOD) {
  if (e == -1) e = m - 2;
  ll ret = 1;
  while (e) {
    if (e & 1) ret = ret * a % m;
    a = a * a % m, e >>= 1;
  }
  return ret;
}

void init() {
  fact[0] = 1;
  for (int i = 1; i < N; i++) {
    fact[i] = 1ll * fact[i - 1] * i % MOD;
  }
  ifact[N - 1] = binExp(fact[N - 1], -1);
  for (int i = N - 2; i >= 0; i--) {
    ifact[i] = 1ll * ifact[i + 1] * (i + 1) % MOD;
  }
}

int nCr(int n, int r) {
  return 1ll * fact[n] * ifact[r] % MOD * ifact[n - r] % MOD;
}

int add(int a, int b) {
  return ((ll)a + b) % MOD;
}

int mul(int a, int b) {
  return (1ll * a * b) % MOD;
}

int F(int n, int k, int a, int i, int l, int r) {
  int ret = a;
  ret = mul(ret, nCr(i - 1, l));
  ret = mul(ret, binExp(a - 1, l));
  ret = mul(ret, binExp(k - a + 1, i - 1 - l));
  ret = mul(ret, nCr(n - i, r));
  ret = mul(ret, binExp(k - a, r));
  ret = mul(ret, binExp(a, n - i - r));
  return ret;
}

int C(int n, int k, int a) {
  int ret = 0;
  for (int i = 1; i <= n; i++) {
    for (int l = 0; l < i; l++) {
      for (int r = l + 1; r <= n - i; r++) {
        ret = add(ret, F(n, k, a, i, l, r));
      }
    }
  }
  return ret;
}

vector<int> generate_values(int n, int k, int m) {
  vector<int> values(m);
  for (int i = 1; i <= m; i++) {
    values[i - 1] = add(i == 1 ? 0 : values[i - 2], C(n, k, i));
  }
  return values;
}

int interpolate(int m, vector<int> values, int k) {
  int ans = 0;
  for (int i = 1; i <= m; i++) {
    int curr = values[i - 1];
    for (int j = 1; j <= m; j++) {
      if (j != i) {
        curr = mul(curr, MOD + k - j);
        curr = mul(curr, binExp(MOD + i - j, -1));
      }
    }
    ans = add(ans, curr);
  }
  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  init();

  int n, k;
  cin >> n >> k;
  int m = n + 2;

  vector<int> values = generate_values(n, k, m);
  cout << (k <= m ? values[k - 1] : interpolate(m, values, k)) << "\n";

  return 0;
}