#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n;
  ll k;
  cin >> n >> k;

  vector<ll> a(n), b;
  for (ll &i : a) cin >> i;
  for (int i = 0; i < n; i++) {
    int vis;
    cin >> vis;
    if (vis) {
      b.push_back(a[i]);
    }
  }

  sort(a.begin(), a.end());
  sort(b.begin(), b.end());

  vector<ll> pref_b(1, 0);
  for (ll i : b) pref_b.push_back(pref_b.back() + i);

  ll ans = 0;
  int m = (n - 1) / 2;

  for (ll picked : b) {
    int nm =
      (picked < a[m]) ? (n % 2 == 1 ? m : m + 1)
      : (picked == a[m]) ? (n % 2 == 1 ? m - 1 : m + 1)
      : (n % 2 == 1 ? m - 1 : m);
    ans = max(ans, (picked + k) + a[nm]);
  }

  for (ll picked : a) {
    if (binary_search(b.begin(), b.end(), picked)) continue;

    ll L = 0, R = int(2e9) + 1;
    while (R - L > 1) {
      ll median = (L + R) / 2;
      bool possible;

      int left = lower_bound(a.begin(), a.end(), median) - a.begin();
      if (picked < median) left--;
      int right = n - 1 - left;
      if (left < right) possible = true;
      else {
        int need = (left - right) / 2 + 1;
        int b_left = lower_bound(b.begin(), b.end(), median) - b.begin();
        if (b_left < need) possible = false;
        else {
          ll sum = pref_b[b_left] - pref_b[b_left - need];
          ll moves = median * need - sum;
          if (moves <= k) possible = true;
          else possible = false;
        }
      }

      if (possible) L = median;
      else R = median;
    }

    ans = max(ans, picked + L);
  }

  cout << ans << '\n';
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