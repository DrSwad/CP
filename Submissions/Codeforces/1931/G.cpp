#include <bits/stdc++.h>
using namespace std;

const int N = 2e6 + 5;
const int mod = 998244353;

int add(int a, int b) {
  int c = a + b;
  return c < mod ? c : c - mod;
}

int mul(int a, int b) {
  return 1ll * a * b % mod;
}

int fact[N], ifact[N], inv[N];

void init() {
  inv[1] = fact[0] = ifact[0] = 1;
  for (int i = 2; i < N; i++) inv[i] = mul(inv[mod % i], mod - mod / i);
  for (int i = 1; i < N; i++) fact[i] = mul(fact[i - 1], i);
  for (int i = 1; i < N; i++) ifact[i] = mul(ifact[i - 1], inv[i]);
}

int C(int n, int k) {
  if (k == n) return 1;
  else if (k<0 or k> n) return 0;
  else return mul(fact[n], mul(ifact[k], ifact[n - k]));
}

void test_case() {
  int c[2][2];
  cin >> c[1][0] >> c[0][1] >> c[0][0] >> c[1][1];

  if (c[0][0] == 0
      and c[0][1] == 0
      and c[1][0] == 0
      and c[1][1] == 0
  ) {
    cout << "1\n";
    return;
  }

  if (abs(c[0][1] - c[1][0]) > 1) {
    cout << "0\n";
    return;
  }

  int ans = 0;

  for (int _ = 0; _ < 2; _++) {
    swap(c[0][1], c[1][0]);
    swap(c[0][0], c[1][1]);
    if (c[0][1] < c[1][0]) continue;

    int s00 = 1 + c[1][0];
    int s11 = c[0][1];

    int w00 = C(c[0][0] + s00 - 1, s00 - 1);
    int w11 = C(c[1][1] + s11 - 1, s11 - 1);
    ans = add(ans, mul(w00, w11));
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