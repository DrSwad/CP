#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<ll> a(n);
  for (ll &i : a) cin >> i;

  int ans = 0;
  for (int mask = 1; mask < 1 << n; mask++) {
    vector<ll> cur_a;
    for (int i = 0; i < n; i++) {
      if (mask >> i & 1) {
        cur_a.push_back(a[i]);
      }
    }

    ll prv_xr = -1;
    bool okay = true;
    for (int i = 1; i < (int)cur_a.size(); i++) {
      ll cur_xr = cur_a[i - 1] ^ cur_a[i];
      if (cur_xr < prv_xr) {
        okay = false;
        break;
      }
      prv_xr = cur_xr;
    }

    if (okay) ans = max(ans, __builtin_popcount(mask));
  }

  cout << ans << "\n";

  return 0;
}