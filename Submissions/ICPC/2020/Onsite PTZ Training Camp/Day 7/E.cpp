#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 1e16;

void test_case() {
  int n;
  cin >> n;

  vector<ll> a(n), b(n), c(n);
  for (ll &i : a) cin >> i;
  for (ll &i : b) cin >> i;
  for (ll &i : c) cin >> i;

  function<bool(ll)> check = [&](ll min_bound) -> bool {
    vector<bool> vis(n + 1, false);
    vis[n] = true;
    ll max_sum = LLONG_MIN;
    for (int i = n - 1; i >= 0; i--) {
      if (a[i] + b[i] + c[i] >= min_bound and vis[i + 1]) {
        vis[i] = true;
      }
      if (max_sum >= min_bound - a[i] - b[i]) {
        vis[i] = true;
      }
      if (max_sum > LLONG_MIN) {
        max_sum += a[i];
      }
      if (vis[i + 1]) {
        max_sum = max(max_sum, a[i] + c[i]);
      }
    }

    return vis[0];
  };

  ll L = -INF, R = INF;
  while (R > L + 1) {
    ll mid = (L + R) / 2;
    if (check(mid)) L = mid;
    else R = mid;
  }

  cout << L << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  // cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}