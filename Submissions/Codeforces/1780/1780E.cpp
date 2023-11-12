#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int l;
  ll r;
  cin >> l >> r;

  ll ans = max(0ll, (r / 2) - (l - 1));

  for (int R = l - 1; R > 0; ) {
    int q = (l + R - 1) / R;
    int L = (l - 1) / q + 1;
    ans += max(0ll, min(r / (q + 1), (ll)R) - L + 1);
    R = L - 1;
  }

  cout << ans << "\n";
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