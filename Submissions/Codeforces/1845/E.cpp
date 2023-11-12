#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

void add(int &a, int b) {
  a += b;
  a >= mod ? (a -= mod) : a;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  int max_diff;
  {
    max_diff = 0;
    int moves = 0;
    while (moves + (max_diff + 1) <= k) {
      moves += max_diff + 1;
      max_diff++;
    }
  }

  vector<int> vis(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> vis[i];
  }

  vector dp(2 * max_diff + 1, vector(k + 1, 0));
  dp[max_diff][k] = 1;

  for (int i = 1, pref = 0; i <= n; i++) {
    vector ndp(2 * max_diff + 1, vector(k + 1, 0));

    int prv_min_diff = max(-max_diff, 0 - pref);
    int prv_max_diff = min(max_diff, (i - 1) - pref);

    pref += vis[i];
    int new_min_diff = max(-max_diff, 0 - pref);
    int new_max_diff = min(max_diff, i - pref);

    for (int prv_diff = prv_min_diff; prv_diff <= prv_max_diff; prv_diff++) {
      for (int prv_k = abs(prv_diff); prv_k <= k; prv_k++) {
        for (int new_vis = 0; new_vis <= 1; new_vis++) {
          int new_diff = prv_diff + new_vis - vis[i];
          if (new_min_diff <= new_diff and new_diff <= new_max_diff) {
            int new_k = prv_k - abs(prv_diff);
            add(ndp[new_diff + max_diff][new_k], dp[prv_diff + max_diff][prv_k]);
          }
        }
      }
    }

    swap(dp, ndp);
  }

  int ans = 0;

  for (int moves = 0; moves <= k; moves += 2) {
    add(ans, dp[max_diff][moves]);
  }

  cout << ans << "\n";

  return 0;
}