#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int A = 1e9;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;
  sort(a.begin(), a.end());

  vector<ll> pref(n + 1);
  pref[0] = 0;
  for (int i = 1; i <= n; i++) {
    pref[i] = pref[i - 1] + a[i - 1];
  }

  auto moves = [&](int new_median) {
    int up = upper_bound(a.begin(), a.end(), new_median) - a.begin();
    int cnt = up - (n - 1) / 2;
    ll psum = pref[up] - pref[(n - 1) / 2];
    ll nsum = (ll)new_median * cnt;
    return nsum - psum;
  };

  int L = a[(n - 1) / 2], R = A;
  while (L != R) {
    int mid = (L + R) / 2;
    if ((ll)mid * n >= pref[n] + moves(mid)) R = mid;
    else L = mid + 1;
  }

  ll m = moves(L);
  ll curr_sum = pref[n] + m;
  ll need_sum = (ll)L * n;
  assert(need_sum >= curr_sum);
  ll ans = m + (need_sum - curr_sum);

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