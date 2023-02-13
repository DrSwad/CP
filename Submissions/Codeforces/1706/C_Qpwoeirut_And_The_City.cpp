#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n;
  cin >> n;

  vector<int> h(n);
  for (int &i : h) cin >> i;

  if (n & 1) {
    ll ans = 0;
    for (int i = 1; i < n - 1; i += 2) {
      ans += max(0, max(h[i + 1], h[i - 1]) + 1 - h[i]);
    }
    cout << ans << "\n";
  }
  else {
    vector<ll> pref(1, 0), suff(1, 0);
    for (int i = 1; i < n - 1; i += 2) {
      pref.push_back(pref.back() + max(0, max(h[i + 1], h[i - 1]) + 1 - h[i]));
    }
    for (int i = n - 2; i > 0; i -= 2) {
      suff.push_back(suff.back() + max(0, max(h[i + 1], h[i - 1]) + 1 - h[i]));
    }
    reverse(suff.begin(), suff.end());

    int sz = pref.size();
    assert(suff.size() == sz);

    ll ans = LLONG_MAX;
    for (int i = 0; i < sz; i++) {
      ans = min(ans, pref[i] + suff[i]);
    }
    cout << ans << "\n";
  }
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