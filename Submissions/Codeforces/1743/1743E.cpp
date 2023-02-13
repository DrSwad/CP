#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  vector<int> p(2);
  vector<ll> t(2);
  int h, s;

  cin >> p[0] >> t[0];
  cin >> p[1] >> t[1];
  cin >> h >> s;

  vector<ll> dp(h + 1);
  dp[0] = 0;

  for (int cur_h = 1; cur_h <= h; cur_h++) {
    dp[cur_h] = LLONG_MAX;
    for (int it = 0; it < 2; it++) {
      for (int sep = 0; sep <= cur_h; sep++) {
        ll cnt_it = sep;
        ll cnt_it2 = (t[it] * (sep + 1) - t[it ^ 1]) / t[it ^ 1];
        ll h_rem = (ll)cur_h - cnt_it * (p[it] - s) - cnt_it2 * (p[it ^ 1] - s);
        if (h_rem <= 0) {
          ll time_passed = max(cnt_it * t[it], cnt_it2 * t[it ^ 1]);
          dp[cur_h] = min(dp[cur_h], time_passed);
        }
        else {
          ll time_passed = (cnt_it + 1) * t[it];
          if (time_passed >= t[it ^ 1]) {
            h_rem = max(0ll, h_rem - p[it] - p[it ^ 1] + s);
            dp[cur_h] = min(dp[cur_h], time_passed + dp[h_rem]);
          }
        }
      }
    }
  }

  cout << dp[h] << "\n";

  return 0;
}