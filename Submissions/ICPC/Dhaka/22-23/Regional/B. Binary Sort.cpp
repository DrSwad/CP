#include <bits/stdc++.h>
using namespace std;

const int BITS = 60;
const int MAX_OP = 3e3;
typedef long long ll;

void test_case() {
  int n;
  cin >> n;

  vector<ll> a(n);
  for (ll &i : a) cin >> i;

  vector dp(2, vector(MAX_OP + 1, -1ll));
  dp[1][0] = 0;

  auto consider = [&](ll &dp, ll val) { dp = dp == -1 ? val : min(dp, val); };

  for (int i = 0; i < n; i++) {
    int ii = i & 1;
    fill(dp[ii].begin(), dp[ii].end(), -1ll);

    for (int prv_op = 0; prv_op <= MAX_OP; prv_op++) {
      if (dp[ii ^ 1][prv_op] == -1) continue;

      ll prv_a = dp[ii ^ 1][prv_op];
      if (prv_a < a[i]) consider(dp[ii][prv_op], a[i]);

      int carry_op = 0;
      ll carry_a = a[i];
      for (int b = BITS - 1; b >= 0; b--) {
        if (!(a[i] >> b & 1) and !(prv_a >> b & 1)) {
          consider(dp[ii][prv_op + carry_op + 1], carry_a + (1ll << b));
        }
        if (!(a[i] >> b & 1) and (prv_a >> b & 1)) {
          carry_op++;
          carry_a += 1ll << b;
        }
      }
    }
  }

  int ans;
  for (ans = 0; ans <= MAX_OP; ans++) {
    if (dp[(n - 1) & 1][ans] >= 0) break;
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}
