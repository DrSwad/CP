#include <bits/stdc++.h>
using namespace std;

const int N = 50;
int mod;

int add(int a, int b) {
  int c = a + b;
  return c < mod ? c : c - mod;
}

int mul(int a, int b) {
  return 1ll * a * b % mod;
}

int n;
int inv_ways[N + 1][N * N];
int inv_ways_suffix[N + 1][N * N];
int fact[N + 1];
int C[N + 1][N + 1];
int dp[N + 1];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> mod;

  inv_ways[1][0] = 1 % mod;
  for (int cur_n = 2; cur_n <= n; cur_n++) {
    int max_inv = cur_n * (cur_n - 1) / 2;
    for (int window = 0, inv = 0; inv <= max_inv; inv++) {
      window = add(window, inv_ways[cur_n - 1][inv]);
      if (inv >= cur_n) window = add(window, mod - inv_ways[cur_n - 1][inv - cur_n]);
      inv_ways[cur_n][inv] = window;
    }
    for (int inv = max_inv; inv >= 0; inv--) {
      inv_ways_suffix[cur_n][inv] = add(inv_ways_suffix[cur_n][inv + 1], inv_ways[cur_n][inv]);
    }
  }

  dp[1] = 0;
  for (int cur_n = 2; cur_n <= n; cur_n++) {
    int max_inv = cur_n * (cur_n - 1) / 2;
    for (int small = 1; small < cur_n; small++) {
      int small_inv = small - 1;
      for (int big = small + 1; big <= cur_n; big++) {
        int big_inv = big - 1;
        for (int big_tot_inv = big - 1; big_tot_inv <= max_inv; big_tot_inv++) {
          int small_tot_inv = big_tot_inv + 1;
          int small_need_inv = max(0, small_tot_inv - small_inv);
          dp[cur_n] = add(dp[cur_n], mul(inv_ways[cur_n - 1][big_tot_inv - big_inv], inv_ways_suffix[cur_n - 1][small_need_inv]));
        }
      }
    }
  }

  fact[0] = 1;
  for (int i = 1; i <= n; i++) {
    fact[i] = mul(fact[i - 1], i);
  }

  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= i; j++) {
      if (i == j) C[i][j] = 1 % mod;
      else C[i][j] = add(C[i - 1][j], C[i - 1][j - 1]);
    }
  }

  int ans = 0;

  for (int pref = 0; pref < n; pref++) {
    ans = add(ans, mul(C[n][pref], mul(fact[pref], dp[n - pref])));
  }

  cout << ans << "\n";

  return 0;
}