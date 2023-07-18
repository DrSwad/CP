#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  ll s, k;
  cin >> s >> k;

  ll ans = 0;

  while (k) {
    ans = max(ans, s * k);
    int d = s % 10;
    if (d == 2 or d == 0) break;
    s += s % 10;
    k--;
  }

  function<bool(ll, ll)> check =
    [&](ll s, ll k) {
      ll base_ans = s * k;
      if (k >= 1 and (s + 2) * (k - 1) >= base_ans) return true;
      if (k >= 2 and (s + 6) * (k - 2) >= base_ans) return true;
      if (k >= 3 and (s + 14) * (k - 3) >= base_ans) return true;
      if (k >= 4 and (s + 20) * (k - 4) >= base_ans) return true;
      return false;
    };

  if (s % 10 == 2) {
    ll L = 0, R = (k % 4 == 0 ? k / 4 : k / 4 + 1);
    while (R - L > 1) {
      ll mid = (L + R) / 2;
      ll ns = s + 20ll * mid;
      ll nk = k - 4ll * mid;
      if (check(ns, nk)) L = mid;
      else R = mid;
    }
    s += 20ll * L;
    k -= 4ll * L;
    ans = max(ans, s * k);
    if (k >= 1) ans = max(ans, (s + 2) * (k - 1));
    if (k >= 2) ans = max(ans, (s + 6) * (k - 2));
    if (k >= 3) ans = max(ans, (s + 14) * (k - 3));
    if (k >= 4) ans = max(ans, (s + 20) * (k - 4));
  }

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