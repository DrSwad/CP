#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll lcm(ll a, ll b, ll mx) {
  if (a == 0 or b == 0) return 0;
  a /= gcd(a, b);
  if (mx / a < b) return 0;
  return a * b;
}

void test_case() {
  int n;
  cin >> n;

  vector<ll> a(n);
  for (ll &i : a) cin >> i;

  ll mx = 1ll * n * n;
  set<ll> lcm_vis;
  set<ll> suff_lcm;

  for (int i = 0; i < n; i++) {
    set<ll> new_suff_lcm;
    new_suff_lcm.insert(a[i]);

    for (ll L : suff_lcm) {
      new_suff_lcm.insert(lcm(L, a[i], mx));
    }

    swap(suff_lcm, new_suff_lcm);

    for (ll L : suff_lcm) {
      lcm_vis.insert(L);
    }
  }

  int ans;
  if (!lcm_vis.empty() and * lcm_vis.begin() == 0) lcm_vis.erase(lcm_vis.begin());
  for (ans = 1; !lcm_vis.empty() and * lcm_vis.begin() == ans; ans++) {
    lcm_vis.erase(lcm_vis.begin());
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}