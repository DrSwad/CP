#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n, p;
  cin >> n >> p;

  vector<int> b(n);
  for (int &i : b) cin >> i;

  vector<ll> pref(n + 1);
  pref[0] = 0;
  for (int i = 0; i < n; i++) {
    pref[i + 1] = pref[i] + b[i];
  }

  ll ans = 0;
  for (int l = 0; l < n; l++) {
    ll mx = pref[l] + p;
    int r = upper_bound(pref.begin(), pref.end(), mx) - pref.begin() - 1;
    ans += max(0, r - l);
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}