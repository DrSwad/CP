#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  int tot_states = 0;
  vector<int> rems;
  vector<vector<pair<int, int>>> trans;

  for (int mul = k; mul >= 1; mul--) {
    int rem = (k + mul - 1) / mul;
    if (rems.empty() or rems.back() != rem) {
      int cur_state = tot_states++;
      rems.emplace_back(rem);
      trans.emplace_back();

      for (int prv_state = 0; prv_state <= cur_state; prv_state++) {
        int prv_rem = rems[prv_state];
        int need_mul = (rem + prv_rem - 1) / prv_rem;
        int got_rem = (rem + need_mul - 1) / need_mul;

        if (got_rem == prv_rem) {
          trans.back().emplace_back(prv_state, need_mul);
        }
      }
    }
  }

  vector<vector<double>> dp(n + 1, vector<double>(tot_states, 0));
  dp[0][tot_states - 1] = k;

  for (int i = 1; i <= n; i++) {
    for (int prv_state = 0; prv_state < tot_states; prv_state++) {
      for (auto [cur_state, b] : trans[prv_state]) {
        if (b <= a[i - 1]) {
          dp[i][cur_state] = max(dp[i][cur_state], dp[i - 1][prv_state] * floor(a[i - 1] / b) / a[i - 1]);
        }
      }
    }
  }

  cout << fixed << setprecision(10) << dp[n][0] << "\n";

  return 0;
}
