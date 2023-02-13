#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int l, r;
  cin >> l >> r;

  vector<ll> div(r + 1, 0);

  for (int d = l; d <= r; d++) {
    for (int m = d + d; m <= r; m += d) {
      div[m]++;
    }
  }

  ll ans = 0;
  for (int k = l; k <= r; k++) {
    ans += 1ll * (k - l) * (k - l - 1) / 2; // add all
    ans -= 1ll * div[k] * (div[k] - 1) / 2; // remove lcm = k

    // lcm = 2k, bad case 1
    if (2 * k % 3 == 0 and 2 * k % 4 == 0) {
      int i = 2 * k / 4;
      int j = 2 * k / 3;
      if (l <= i and (k % i != 0 or k % j != 0)) ans--;
    }

    // lcm = 2k, bad case 2
    if (2 * k % 3 == 0 and 2 * k % 5 == 0) {
      int i = 2 * k / 5;
      int j = 2 * k / 3;
      if (l <= i and (k % i != 0 or k % j != 0)) ans--;
    }
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