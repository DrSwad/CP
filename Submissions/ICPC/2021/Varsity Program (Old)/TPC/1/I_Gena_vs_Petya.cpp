#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 2e5 + 5;
const int LOG_A = 60;

int n;
ll a[N];
ll dp[LOG_A][N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];

  int cnt[2]{0, 0};
  for (int i = 1; i <= n; i++) {
    cnt[a[i] & 1]++;
  }
  dp[0][0] += cnt[1] % 2 == 0 ? 1 : 0;
  dp[0][cnt[0]] += cnt[0] % 2 == 0 ? 1 : 0;

  vector<int> order(n);
  iota(order.begin(), order.end(), 1);

  for (int b = 1; b < LOG_A; b++) {
    vector<int> norder;
    for (int i : order) {
      if ((a[i] >> (b - 1) & 1) == 0) norder.push_back(i);
    }
    for (int i : order) {
      if ((a[i] >> (b - 1) & 1) == 1) norder.push_back(i);
    }
    order = norder;

    vector<int> pref(n + 1);
    pref[0] = 0;
    for (int i = 1; i <= n; i++) {
      pref[i] = pref[i - 1] + (a[order[i - 1]] >> b & 1);
    }

    for (int carry = 0; carry <= n; carry++) {
      int carry_with_bit[2][2];
      carry_with_bit[1][1] = pref[carry];
      carry_with_bit[1][0] = carry - pref[carry];
      carry_with_bit[0][1] = pref[n] - carry_with_bit[1][1];
      carry_with_bit[0][0] = n - carry_with_bit[1][1] - carry_with_bit[1][0] - carry_with_bit[0][1];

      for (int k_bit = 0; k_bit < 2; k_bit++) {
        int new_carry = 0;
        int new_ones = 0;

        for (int carry_bit = 0; carry_bit < 2; carry_bit++) {
          int s_bit = k_bit + carry_bit;

          for (int a_bit = 0; a_bit < 2; a_bit++) {
            int freq = carry_with_bit[carry_bit][a_bit];
            int c_bit = a_bit - s_bit;
            if (c_bit < 0) {
              c_bit += 2;
              new_carry += freq;
            }
            if (c_bit == 1) {
              new_ones += freq;
            }
          }
        }

        if (new_ones % 2 == 0) {
          dp[b][new_carry] += dp[b - 1][carry];
        }
      }
    }
  }

  ll ans = dp[LOG_A - 1][0];

  ll mn = *min_element(a + 1, a + n + 1);
  ll xr = 0;
  for (int i = 1; i <= n; i++) {
    xr ^= a[i] - mn;
  }
  ans -= xr == 0;

  cout << ans << "\n";

  return 0;
}