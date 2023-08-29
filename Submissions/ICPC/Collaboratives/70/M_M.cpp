#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int mod = 1e9 + 7;
const ll inf = 1ll << 61;
const int inv2 = (mod + 1) / 2;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<ll> b(n);
  for (ll &i : b) cin >> i;

  ll cur = 2;
  bool inf_reached = false;

  for (int i = 0; i < n; i++) {
    if (cur >= inf) inf_reached = true, cur %= mod;
    if (inf_reached) cur = (2ll * (cur - b[i] % mod + mod)) % mod;
    else {
      if (cur < b[i]) {
        cout << "error\n";
        return 0;
      }
      cur = 2ll * (cur - b[i]);
    }
  }

  cout << cur % mod * inv2 % mod << "\n";

  return 0;
}