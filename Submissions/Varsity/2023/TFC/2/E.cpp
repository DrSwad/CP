#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  vector<ll> a(n);
  for (ll &i : a) cin >> i;

  vector<vector<pair<ll, int>>> dp(n);
  dp[n - 1] = {{LLONG_MAX, 1}};

  for (int i = n - 2; i >= 0; i--) {
    // DB();
    // debug(i);

    dp[i] = {{LLONG_MAX, 1}};
    for (int j = i + 1; j < n; j++) {
      ll xr = a[i] ^ a[j];
      auto it = lower_bound(dp[j].begin(), dp[j].end(), make_pair(xr, 0));
      assert(it != dp[j].end());
      dp[i].emplace_back(xr, it->second + 1);
    }
    sort(dp[i].begin(), dp[i].end());
    // debug(dp);

    vector<pair<ll, int>> ndp{{LLONG_MAX, 1}};

    for (int j = (int)dp[i].size() - 2; j >= 0; j--) {
      if (dp[i][j].first < dp[i][j + 1].first) {
        dp[i][j].second = max(dp[i][j].second, ndp.back().second);
        ndp.emplace_back(dp[i][j]);
      }
    }

    reverse(ndp.begin(), ndp.end());
    swap(dp[i], ndp);

    // debug(dp[i]);
  }

  int ans = 0;
  for (int i = 0; i < n; i++) {
    ans = max(ans, dp[i][0].second);
  }

  cout << ans << "\n";

  return 0;
}
// {6, 6, 5, 1, 7, 0}