#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, h;
  cin >> n >> h;

  vector<int> x(n);
  for (int &i : x) cin >> i;

  vector<vector<pair<int, ll>>> dp1(n, vector<pair<int, ll>>(n));

  for (int i = 0; i < n; i++) {
    dp1[i][i] = {0, 0ll};
  }

  function<pair<int, ll>(int, int)> merge_two = [&](int x_l, int x_r) {
    assert(x_l < x_r);
    int moves = (x_r - x_l + 1) / 2;
    return make_pair(moves, 2ll * moves);
  };
  
  for (int l = n - 1; l >= 0; l--) {
    for (int r = l + 1; r < n; r++) {
      for (int m = l; m < r; m++) {
        auto [moves_l, lego_l] = dp1[l][m];
        auto [moves_r, lego_r] = dp1[m + 1][r];

        int x_l = x[l] + moves_l;
        int x_r = x[r] - moves_r;

        if (moves_l < moves_r) {
          x_l += moves_r - moves_l;
          lego_l += moves_r - moves_l;
          moves_l = moves_r;
        }
        if (moves_l > moves_r) {
          x_r -= moves_l - moves_r;
          lego_r += moves_l - moves_r;
          moves_r = moves_l;
        }

        auto [moves_m, lego_m] = merge_two(x_l, x_r);
        int tot_moves = moves_l + moves_m;
        ll tot_lego = lego_l + lego_r + lego_m;
        if (m == l or tot_lego < dp1[l][r].second) {
          dp1[l][r] = make_pair(tot_moves, tot_lego);
        }
      }
    }
  }

  vector<vector<ll>> cost(n, vector<ll>(n, -1));
  for (int l = 0; l < n; l++) {
    for (int r = l; r < n; r++) {
      auto [moves, lego] = dp1[l][r];
      if (moves > h) cost[l][r] = -1ll;
      else cost[l][r] = lego + (h + 1 - moves);
    }
  }

  vector<vector<ll>> dp2(n, vector<ll>(n, LLONG_MAX));

  for (int l = n - 1; l >= 0; l--) {
    for (int r = l; r < n; r++) {
      if (cost[l][r] != -1) dp2[l][r] = cost[l][r];
      for (int m = l; m < r; m++) {
        if (cost[m + 1][r] != -1) {
          dp2[l][r] = min(dp2[l][r], dp2[l][m] + cost[m + 1][r]);
        }
      }
    }
  }

  cout << dp2[0][n - 1] - n << "\n";

  return 0;
}
