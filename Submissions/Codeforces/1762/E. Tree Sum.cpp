#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 5e5 + 5;
const int mod = 998244353;

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

int trees[N], fact[N], ifact[N];

void init() {
  trees[1] = 1;
  for (int i = 2; i < N; i++) {
    trees[i] = binExp(i, i - 2);
  }

  fact[0] = 1;
  for (int i = 1; i < N; i++) {
    fact[i] = mul(fact[i - 1], i);
  }
  ifact[N - 1] = binExp(fact[N - 1], -1);
  for (int i = N - 2; i >= 0; i--) {
    ifact[i] = mul(ifact[i + 1], i + 1);
  }
}

int C(int n, int k) {
  if (k < 0 or k > n) return 0;
  return mul(fact[n], mul(ifact[k], ifact[n - k]));
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  if (n % 2 == 1) cout << "0\n";
  else {
    init();

    int ans = 0;

    if (n > 2) {
      for (int sz = 2; sz < n; sz++) {
        int to_add = mul(C(n - 3, sz - 2), trees[sz]);
        if (sz % 2 == 1) to_add = mod - to_add;
        to_add = mul(to_add, mul(trees[n - sz], n - sz));
        ans = add(ans, to_add);
      }
      ans = mul(ans, n - 2);
    }

    for (int sz = 1; sz < n; sz++) {
      int to_add = mul(C(n - 2, sz - 1), trees[sz]);
      if (sz % 2 == 1) to_add = mod - to_add;
      to_add = mul(to_add, mul(trees[n - sz], n - sz));
      ans = add(ans, to_add);
    }

    cout << ans << "\n";
  }

  return 0;
}
