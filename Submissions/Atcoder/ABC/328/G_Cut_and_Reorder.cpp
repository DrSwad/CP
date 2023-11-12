#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 22;
const int max_size = 2.1e6;

int n;
ll c;
ll a[N], b[N];
ll dp[max_size][N];
ll dp_mn[1 << N][2];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> c;
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < n; i++) cin >> b[i];

  for (int mask = 1; mask < 1 << n; mask++) {
    int _mask = mask % max_size;
    dp_mn[mask][0] = dp_mn[mask][1] = LLONG_MAX;

    for (int last = 0; last < n; last++) {
      dp[_mask][last] = LLONG_MAX;
      if (mask >> last & 1) {
        int prv_mask = mask ^ 1 << last;
        int _prv_mask = prv_mask % max_size;
        if (prv_mask == 0) {
          ll cur = abs(a[last] - b[__builtin_popcount(mask) - 1]);
          if (last != 0) cur += c;
          dp[_mask][last] = min(dp[_mask][last], cur);
        }
        else {
          if (last - 1 >= 0 and prv_mask >> (last - 1) & 1) {
            dp[_mask][last] = min(dp[_mask][last], dp[_prv_mask][last - 1]);
          }

          ll cur = last - 1 >= 0 and dp[_prv_mask][last - 1] == dp_mn[prv_mask][0] ? dp_mn[prv_mask][1] : dp_mn[prv_mask][0];
          if (cur < LLONG_MAX) {
            dp[_mask][last] = min(dp[_mask][last], cur + (last > 0 ? c : 0));
          }

          dp[_mask][last] += abs(a[last] - b[__builtin_popcount(mask) - 1]);
        }

        if (dp[_mask][last] <= dp_mn[mask][0]) {
          dp_mn[mask][1] = dp_mn[mask][0];
          dp_mn[mask][0] = dp[_mask][last];
        }
        else if (dp[_mask][last] <= dp_mn[mask][1]) {
          dp_mn[mask][1] = dp[_mask][last];
        }
      }
    }
  }

  ll ans = LLONG_MAX;
  int mask = ((1 << n) - 1) % max_size;
  for (int i = 0; i < n; i++) {
    ans = min(ans, dp[mask][i]);
  }

  cout << ans << "\n";

  return 0;
}