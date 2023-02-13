#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int h, p;
  cin >> h >> p;

  int r = 0;
  ll ans = 0;

  for (int i = 0; i < h; i++) {
    ll tot = 1ll << i;
    if (tot <= p) ans++;
    else {
      if (r) {
        tot = max(tot - (p - r), 2ll * r);
      }
      ans += (tot + p - 1) / p;
      r = tot % p;
    }
  }

  cout << ans << "\n";
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