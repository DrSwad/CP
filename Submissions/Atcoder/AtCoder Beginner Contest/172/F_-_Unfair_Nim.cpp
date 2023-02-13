#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 305;
const int BLK_SZ = 1 << 20;
const int BLK_LOG = 20;

int n;
ll a[N];
ll x;

ll try_interval(ll d) {
  ll dl = max(d, 0ll);
  ll dr = min(d + BLK_SZ, a[0]);
  for (ll d = dl; d < dr; d++) {
    if (((a[0] - d) ^ (a[1] + d)) == x) {
      return d;
    }
  }
  return -1;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;

  for (int i = 0; i < n; i++) {
    cin >> a[i];
    if (i >= 2) x ^= a[i];
  }
  ll xx = x >> BLK_LOG;

  ll ans = -1;
  for (ll d = 0; d < a[0]; d += BLK_SZ) {
    ll al = max(0ll, a[0] - d - (BLK_SZ - 1));
    ll ar = a[0] - d;
    al >>= BLK_LOG, ar >>= BLK_LOG;

    ll bl = a[1] + d;
    ll br = a[1] + d + (BLK_SZ - 1);
    bl >>= BLK_LOG, br >>= BLK_LOG;

    if ((al ^ bl) == xx or (al ^ br) == xx or
        (ar ^ bl) == xx or (ar ^ br) == xx
        ) {
      ans = try_interval(d);
      if (ans != -1) break;
    }
  }

  cout << ans << "\n";

  return 0;
}