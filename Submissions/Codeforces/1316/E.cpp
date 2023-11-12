#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, p, k;
  cin >> n >> p >> k;

  vector v(n, vector<int>(p + 1));
  for (int i = 0; i < n; i++) cin >> v[i][0];
  for (int i = 0; i < n; i++) {
    for (int j = 1; j <= p; j++) {
      cin >> v[i][j];
    }
  }

  sort(v.begin(), v.end(), greater<vector<int>>());

  vector<ll> prv_dp(1 << p), cur_dp(1 << p);
  fill(cur_dp.begin(), cur_dp.end(), -1);
  cur_dp[0] = 0;

  for (int i = 0; i < n; i++) {
    swap(cur_dp, prv_dp);
    fill(cur_dp.begin(), cur_dp.end(), -1);

    for (int mask = 0; mask < 1 << p; mask++) {
      int p_cnt = __builtin_popcount(mask);
      int k_cnt = (i + 1) - p_cnt;
      if (p_cnt <= i + 1) {
        if (prv_dp[mask] >= 0) {
          cur_dp[mask] = prv_dp[mask] + (k_cnt <= k ? v[i][0] : 0);
        }

        for (int j = 0; j < p; j++) {
          if (mask >> j & 1) {
            int prv_mask = mask ^ 1 << j;
            if (prv_dp[prv_mask] >= 0) {
              cur_dp[mask] = max(cur_dp[mask], prv_dp[prv_mask] + v[i][j + 1]);
            }
          }
        }
      }
    }
  }

  cout << cur_dp[(1 << p) - 1] << "\n";

  return 0;
}