#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 1e9 + 7;

ll binExp(ll a, ll e, ll m = MOD) {
  if (e == -1) e = m - 2;
  ll ret = 1;
  while (e) {
    if (e & 1) ret = ret * a % m;
    a = a * a % m, e >>= 1;
  }
  return ret;
}

int main() {
  ll a, b, n, x;
  cin >> a >> b >> n >> x;

  ll an = binExp(a, n);
  ll sum = a == 1 ? n % MOD : (an + MOD - 1) * binExp(a + MOD - 1, -1) % MOD;

  ll ans = (an * x % MOD + sum * b % MOD) % MOD;
  cout << ans << endl;

  return 0;
}