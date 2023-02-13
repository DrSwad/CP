#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int l, r;
  cin >> l >> r;

  const int mod = 2019;

  if (r - l + 1 >= mod) cout << 0 << "\n";
  else {
    ll ans = mod;
    for (int i = l; i <= r; i++) {
      for (int j = i + 1; j <= r; j++) {
        ans = min(ans, (ll)i * j % mod);
      }
    }
    cout << ans << "\n";
  }

  return 0;
}