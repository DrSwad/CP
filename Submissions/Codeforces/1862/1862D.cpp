#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  ll n;
  cin >> n;

  ll L = 0, R = 2e9;
  while (R - L > 1) {
    ll mid = (L + R) / 2;
    if (mid * (mid + 1) / 2 <= n) L = mid;
    else R = mid;
  }

  ll got = L * (L + 1) / 2;
  ll ans = (L + 1) + (n - got);

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