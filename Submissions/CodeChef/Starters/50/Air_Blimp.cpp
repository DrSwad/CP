#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n;
  ll x, y;
  cin >> n >> x >> y;

  vector<ll> a(n);
  for (ll &i : a) cin >> i;

  ll ans = 0;
  for (int i = n - 1; i >= 0; i--) {
    if (a[i] <= ans * y) continue;
    ll z = max(x, y);
    ll moves = (a[i] - ans * y + z - 1) / z;
    ans += moves;
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}