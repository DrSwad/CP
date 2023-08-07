#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll binExp(ll a, ll e, ll m) {
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

  int a, b, p;
  ll x;
  cin >> a >> b >> p >> x;

  ll ans = 0;
  for (int r0 = 0, ia = binExp(a, -1, p), A = 1; r0 < p - 1; r0++) {
    int r1 = 1ll * b * A % p;
    ll M = 1ll * p * (p - 1);
    ll n = (1ll * (p - 1) * (M - r1) + 1ll * p * r0) % M;
    ll last = x % M == 0 ? M : x % M;
    ans += (x - 1) / M + (last >= n);
    A = 1ll * A * ia % p;
  }

  cout << ans << "\n";

  return 0;
}