#include <bits/stdc++.h>
using namespace std;

// Case 0: i != j and si != sj => (0, 2, 24)
// Case 1: i != j and si == sj => (1, 0, 25)
// Case 2: i == j => (1, 25, 0)

const int N = 1e6 + 5;
const int mod = 1e9 + 7;

int add(int a, int b) {
  int c = a + b;
  return c < mod ? c : c - mod;
}

int mul(int a, int b) {
  return 1ll * a * b % mod;
}

int fact[N], inv[N], ifact[N];

void init() {
  inv[1] = fact[0] = ifact[0] = 1;
  for (int i = 2; i < N; i++) inv[i] = mul(inv[mod % i], (mod - mod / i));
  for (int i = 1; i < N; i++) fact[i] = mul(fact[i - 1], i);
  for (int i = 1; i < N; i++) ifact[i] = mul(ifact[i - 1], inv[i]);
}

int nCk(int n, int k) {
  if (k<0 or k> n) return 0;
  return mul(fact[n], mul(ifact[k], ifact[n - k]));
}

vector<int> poly_pow(int c0, int c1, int e0, int e1, int exp) {
  vector<int> ret;

  vector<int> pow_c0(exp + 1), pow_c1(exp + 1);
  pow_c0[0] = pow_c1[0] = 1;
  for (int i = 1; i <= exp; i++) {
    pow_c0[i] = mul(pow_c0[i - 1], c0);
    pow_c1[i] = mul(pow_c1[i - 1], c1);
  }

  for (int take0 = 0; take0 <= exp; take0++) {
    int take1 = exp - take0;
    int E = take0 * e0 + take1 * e1;
    while (E > (int)ret.size() - 1) ret.push_back(0);
    ret[E] = add(ret[E], mul(nCk(exp, take0), mul(pow_c0[take0], pow_c1[take1])));
  }

  return ret;
}

void test_case() {
  int n, k;
  cin >> n >> k;

  string s;
  cin >> s;

  int case0_cnt = 0, case1_cnt = 0, case2_cnt = 0;
  for (int i = 0, j = n - 1; i <= j; i++, j--) {
    if (i != j) {
      if (s[i] != s[j]) case0_cnt++;
      else case1_cnt++;
    }
    else case2_cnt++;
  }

  vector<int> poly0 = poly_pow(2, 24, 1, 2, case0_cnt);
  vector<int> poly1 = poly_pow(1, 25, 0, 2, case1_cnt);
  vector<int> poly2 = poly_pow(1, 25, 0, 1, case2_cnt);

  vector<int> poly12;
  for (int e1 = 0; e1 < poly1.size(); e1++) {
    for (int e2 = 0; e2 < poly2.size(); e2++) {
      int e12 = e1 + e2;
      while (e12 > (int)poly12.size() - 1) poly12.push_back(0);
      poly12[e12] = add(poly12[e12], mul(poly1[e1], poly2[e2]));
    }
  }
  while (poly12.size() < n + 1) poly12.push_back(0);
  while (poly0.size() < k + 1) poly0.push_back(0);

  vector<int> pref12(n + 1, 0);
  pref12[0] = poly12[0];
  for (int i = 1; i <= n; i++) {
    pref12[i] = add(poly12[i], pref12[i - 1]);
  }

  int ans = 0;
  for (int e0 = 0; e0 <= k; e0++) {
    int max_e12 = k - e0;
    ans = add(ans, mul(poly0[e0], pref12[max_e12]));
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  init();

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}