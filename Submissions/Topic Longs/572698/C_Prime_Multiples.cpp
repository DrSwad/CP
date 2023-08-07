#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int mod[2] = {int(1e9) + 7, int(1e9) + 9};

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

  ll n;
  cin >> n;

  int k;
  cin >> k;
  vector<ll> p(k);
  for (ll &i : p) cin >> i;

  int rem[2] = {0};

  for (int it = 0; it < 2; it++) {
    for (int mask = 1; mask < 1 << k; mask++) {
      ll mul = 1;
      for (int i = 0; i < k; i++) {
        if (mask >> i & 1) {
          if (n / mul >= p[i]) mul *= p[i];
          else {
            mul = -1;
            break;
          }
        }
      }
      if (mul != -1) {
        if (__builtin_popcount(mask) % 2 == 1) {
          rem[it] += n / mul % mod[it];
        }
        else{
          rem[it] += mod[it] - n / mul % mod[it];
        }
        if (rem[it] >= mod[it]) rem[it] -= mod[it];
      }
    }
  }

  ll tot_mod = (ll)mod[0] * mod[1];
  ll ans =
    (ll)mod[0] * ((ll)rem[1] * binExp(mod[0], -1, mod[1]) % mod[1]) +
    (ll)mod[1] * ((ll)rem[0] * binExp(mod[1], -1, mod[0]) % mod[0]);
  cout << (ans % tot_mod) << "\n";

  return 0;
}