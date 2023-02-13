#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n;
  cin >> n;

  vector<ll> a(n);
  for (ll &i : a) cin >> i;

  sort(a.begin(), a.end());
  ll tot = 0;
  for (ll i : a) tot += i;

  int m;
  cin >> m;

  while (m--) {
    ll x, y;
    cin >> x >> y;

    auto it = lower_bound(a.begin(), a.end(), x);
    ll ans = LLONG_MAX;

    if (it != a.end()) {
      ans = min(ans, max(0ll, y - (tot - *it)));
    }

    if (it != a.begin()) {
      it--;
      ans = min(ans, (x - *it) + max(0ll, y - (tot - *it)));
    }

    cout << ans << "\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  // cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}