#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 1e9 + 7;

ll bigMod(ll a, ll e) {
  if (e == -1) e = MOD - 2;
  ll ret = 1;
  while (e) {
    if (e & 1) ret = ret * a % MOD;
    a = a * a % MOD, e >>= 1;
  }
  return ret;
}

vector<ll> berlekampMassey(vector<int> s) {
  if (s.empty()) return {};
  int n = s.size(), L = 0, m = 0;
  vector<ll> C(n), B(n), T;
  C[0] = B[0] = 1; ll b = 1;
  for (int i = 0; i < n; ++i) {
    ++m; ll d = s[i] % MOD;
    for (int j = 1; j <= L; ++j) d = (d + C[j] * s[i - j]) % MOD;
    if (!d) continue;
    T = C; ll coeff = d * bigMod(b, -1) % MOD;
    for (int j = m; j < n; ++j) C[j] = (C[j] - coeff * B[j - m]) % MOD;
    if (2 * L > i) continue;
    L = i + 1 - L, B = T, b = d, m = 0;
  }
  C.resize(L + 1), C.erase(C.begin());
  for (ll &x : C) x = (MOD - x) % MOD;
  return C;
}

int main() {
  int n; cin >> n;
  vector<int> s(n);
  for (auto &it : s) scanf("%d", &it);
  vector<ll> r = berlekampMassey(s);
  cout << r.size() << '\n';
  for (auto &it : r) printf("%lld ", it);
  cout << '\n';
  return 0;
}
