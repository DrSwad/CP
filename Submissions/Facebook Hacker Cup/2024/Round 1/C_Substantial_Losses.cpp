#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll mod = 998244353;

void test_case() {
  /*
     dp[0] = 1
     dp[L] = 1 / 2 + 1 / 2 * (1 + dp[L-1] + dp[L])
     => 2 * dp[L] = 2 + dp[L-1] + dp[L]
     => dp[L] = 2 + dp[L-1]
     => dp[L] = 2 * L + 1
   */

  ll w, g, l;
  cin >> w >> g >> l;
  ll ans = ((w - g) % mod) * ((2 * l + 1) % mod) % mod;
  cout << ans << "\n";
}

int main() {
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}