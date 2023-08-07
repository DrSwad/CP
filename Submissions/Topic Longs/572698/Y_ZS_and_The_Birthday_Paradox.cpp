#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int mod = 1e6 + 3;

int add(int a, int b) {
  int c = a + b;
  return c < mod ? c : c - mod;
}

int mul(int a, int b) {
  return 1ll * a * b % mod;
}

ll binExp(ll a, ll e, ll m = mod) {
  if (e == -1) e = m - 2;
  ll ret = 1;
  while (e) {
    if (e & 1) ret = ret * a % m;
    a = a * a % m, e >>= 1;
  }
  return ret;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ll n, k;
  cin >> n >> k;

  int msb_k = 63 - __builtin_clzll(k);
  int min_n = (k == 1ll << msb_k) ? msb_k : msb_k + 1;
  if (n < min_n) {
    cout << "1 1\n";
    return 0;
  }

  ll exp = n;
  for (ll p = 2; p <= k - 1; p *= 2) {
    exp += (k - 1) / p;
  }

  int A = 1, B;
  for (int cur = binExp(2, n), i = 0; i < k and A; cur = add(cur, mod - 1), i++) {
    A = mul(A, cur);
  }
  A = mul(A, binExp(binExp(2, exp), -1));
  B = binExp(binExp(2, n), k);
  B = mul(B, binExp(binExp(2, exp), -1));
  A = add(B, mod - A);

  cout << A << " " << B << "\n";

  return 0;
}