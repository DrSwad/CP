#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> c(n);
  vector need(n, vector(2, 0));
  for (int i = 0; i < n; i++) {
    char color;
    cin >> color >> need[i][0] >> need[i][1];
    c[i] = color == 'B';
  }

  int max_discount_0 = n * (n - 1) / 2;
  vector dp(1 << n, vector(max_discount_0 + 1, -1));
  dp[0][0] = 0;

  vector tot_need(1 << n, vector(2, 0));
  vector tot_color(1 << n, vector(2, 0));

  for (int mask = 1; mask < 1 << n; mask++) {
    for (int color = 0; color < 2; color++) {
      int lsb = __builtin_ctz(mask);
      tot_need[mask][color] = tot_need[mask - (1 << lsb)][color] + need[lsb][color];
      tot_color[mask][color] = tot_color[mask - (1 << lsb)][color] + (c[lsb] == color);
    }

    for (int last = 0; last < n; last++) {
      if ((mask >> last & 1) == 0) continue;
      int prv_mask = mask - (1 << last);
      for (int prv_discount_0 = 0; prv_discount_0 <= max_discount_0; prv_discount_0++) {
        int prv_discount_1 = dp[prv_mask][prv_discount_0];
        if (prv_discount_1 == -1) continue;

        int cur_discount_0 = prv_discount_0 + min(need[last][0], tot_color[prv_mask][0]);
        int cur_discount_1 = prv_discount_1 + min(need[last][1], tot_color[prv_mask][1]);
        dp[mask][cur_discount_0] = max(dp[mask][cur_discount_0], cur_discount_1);
      }
    }
  }

  int mask = (1 << n) - 1;
  int ans = INT_MAX;
  for (int discount_0 = 0; discount_0 <= max_discount_0; discount_0++) {
    int discount_1 = dp[mask][discount_0];
    if (discount_1 == -1) continue;
    ans = min(ans, max(tot_need[mask][0] - discount_0, tot_need[mask][1] - discount_1) + n);
  }

  cout << ans << "\n";

  return 0;
}