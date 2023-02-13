#include <bits/stdc++.h>
using namespace std;

/*
   Cases:
   1. One of the segments is a single element
   2. Both of length at-least 2
     1. L1 = 1 <= R1 < L2 = R1 + 1 <= R2 = n
     2. L1 = 1 < L2 < R1 < R2 = n
     3. L1 = 1 < L2 = 2 <= R2 = n - 1 < R1 = n
 */

typedef long long ll;

int n;
vector<ll> a;

ll solve1() {
  vector<ll> pref(n + 1);
  pref[0] = 0;
  for (int i = 0; i < n; i++) {
    pref[i + 1] = pref[i] + a[i];
  }

  auto squash = [&](int at) {
    ll before = (ll)at * a[at] - pref[at];
    ll after = (pref[n] - pref[at]) - (ll)(n - at) * a[at];
    return before + after;
  };

  ll ret = LLONG_MAX;

  for (int i = 0; i < n; i++) {
    int m = n / 2;
    if (i >= m) m--;
    ret = min(ret, squash(m) - abs(a[i] - a[m]));
  }

  return ret;
}

ll solve21() {
  if (n < 4) return LLONG_MAX;

  ll ret = LLONG_MAX;
  for (int i = 1; i < n - 2; i++) {
    ret = min(ret, abs((a[i] - a[0]) - (a[n - 1] - a[i + 1])));
  }
  return ret;
}

ll solve22() {
  if (n < 4) return LLONG_MAX;

  auto closest = [&](const multiset<ll> &st, ll val) {
    ll ret = LLONG_MAX;
    auto it = st.lower_bound(val);
    if (it != st.end()) ret = min(ret, *it - val);
    if (it != st.begin()) it--, ret = min(ret, val - *it);
    return ret;
  };

  ll ret = LLONG_MAX;
  multiset<ll> st;

  for (int i = 2; i < n - 1; i++) {
    st.insert(a[n - 1] - a[i - 1]);
    ret = min(ret, closest(st, a[i] - a[0]));
  }

  return ret;
}

ll solve23() {
  if (n < 4) return LLONG_MAX;
  return (a[1] - a[0]) + (a[n - 1] - a[n - 2]);
}

void test_case() {
  cin >> n;

  a.assign(n, 0ll);
  for (ll &i : a) cin >> i;

  sort(a.begin(), a.end());

  cout << min(
    solve1(),
    min(
      solve21(),
      min(
        solve22(),
        solve23()
        )
      )
      ) << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}