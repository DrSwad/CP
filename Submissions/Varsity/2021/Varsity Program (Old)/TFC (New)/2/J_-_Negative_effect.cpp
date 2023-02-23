#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n, m;
  cin >> n >> m;

  vector<int> a(n);
  ll tot = 0;
  for (int &i : a) cin >> i, tot += i;

  ll pref_sum = 0;
  for (int i = 0; i < n; i++) {
    ll ans = LLONG_MIN;
    if (i > 0) ans = max(ans, pref_sum);
    pref_sum += a[i];
    ans = max(ans, tot - a[i] + m);
    if (i < n - 1) ans = max(ans, tot - pref_sum);

    if (i > 0) cout << " ";
    cout << ans;
  }
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