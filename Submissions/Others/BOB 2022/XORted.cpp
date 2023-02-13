#include <bits/stdc++.h>
using namespace std;

const int B = 20;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<vector<int>> pref(B, vector<int>(n, 0));

  for (int i = 0; i < n - 1; i++) {
    int xr = a[i] ^ a[i + 1];
    if (xr) pref[31 - __builtin_clz(xr)][i + 1]++;
  }

  for (int b = 0; b < B; b++) {
    for (int i = 1; i < n; i++) pref[b][i] += pref[b][i - 1];
  }

  int q;
  cin >> q;

  while (q--) {
    int l, r;
    cin >> l >> r;
    l--, r--;

    int zero_mask = 0;
    for (int b = 0; b < B; b++) {
      if (pref[b][r] > pref[b][l]) {
        zero_mask ^= 1 << b;
      }
    }

    int nums[2] = {a[l], a[r]};
    int adj_nums[2] = {l ? a[l - 1] : 0, r < n - 1 ? a[r + 1] : (1 << B) - 1};

    vector<int> dp(4, 0);
    dp[0] = 1;

    for (int b = B - 1; b >= 0; b--) {
      vector<int> ndp(4, 0);
      for (int old_state = 0; old_state < 4; old_state++) {
        for (int x = 0; x < 2; x++) {
          if (x and (zero_mask >> b & 1)) continue;

          int new_nums[2], new_adj_nums[2];
          for (int it = 0; it < 2; it++) {
            new_nums[it] = (((old_state >> it & 1) ^ it) << 1) + ((nums[it] >> b & 1) ^ x);
            new_adj_nums[it] = ((it) << 1) + (adj_nums[it] >> b & 1);
          }

          if (new_nums[0] < new_adj_nums[0] or new_nums[1] > new_adj_nums[1]) continue;
          int new_state = ((new_nums[1] < new_adj_nums[1]) << 1) + (new_nums[0] > new_adj_nums[0]);
          ndp[new_state] += dp[old_state];
        }
      }
      swap(dp, ndp);
    }

    int ans = accumulate(dp.begin(), dp.end(), 0);
    cout << ans << "\n";
  }
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