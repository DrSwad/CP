#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n;
  cin >> n;

  ll L;
  cin >> L;

  vector<pair<ll, ll>> ranges(n);
  for (auto & [l, r] : ranges) {
    cin >> l >> r;
  }

  int ans1 = 0;
  {
    map<ll, ll> mp_l;
    for (auto [l, r] : ranges) {
      mp_l[l] = max(mp_l[l], r);
    }

    ll at_l = 0, at_r = mp_l[0], nxt_r = at_r;
    ans1++;
    mp_l.erase(0);

    for (auto [l, r] : mp_l) {
      if (l < at_r) nxt_r = max(nxt_r, r);
      else {
        ans1++;
        at_r = nxt_r;
      }
    }

    ans1 += nxt_r != at_r;
  }

  int ans2 = 0;
  {
    map<ll, ll> mp;
    for (auto [l, r] : ranges) {
      mp[l]++;
      mp[r]--;
    }

    int pref = 0, mn = n;
    for (auto [key, val] : mp) {
      pref += val;
      if (key < L) mn = min(mn, pref);
    }

    ans2 = n - (mn - 1);
  }

  cout << ans1 << " " << ans2 << endl;
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