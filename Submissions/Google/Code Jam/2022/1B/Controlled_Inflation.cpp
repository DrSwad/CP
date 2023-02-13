#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n, p;
  cin >> n >> p;

  vector<vector<ll>> a(n, vector<ll>(p));
  for (auto &v : a) {
    for (auto &x : v) {
      cin >> x;
    }
    sort(v.begin(), v.end());
  }
  a.insert(a.begin(), vector<ll>(p, 0));
  a.push_back(a.back());

  vector<vector<ll>> dp(n + 2, vector<ll>(p, 0));
  for (int i = n; i >= 0; i--) {
    ll from_min = LLONG_MAX, from_max = LLONG_MAX;
    for (int j = 0; j < p; j++) {
      from_min = min(from_min, dp[i + 1][j] + abs(a[i][0] - a[i + 1][j]));
      from_max = min(from_max, dp[i + 1][j] + abs(a[i][p - 1] - a[i + 1][j]));
    }

    for (int j = 0; j < p; j++) {
      dp[i][j] = LLONG_MAX;
      dp[i][j] = min(dp[i][j], 2ll * (a[i][p - 1] - a[i][j]) + (a[i][j] - a[i][0]) + from_min);
      dp[i][j] = min(dp[i][j], (a[i][p - 1] - a[i][j]) + 2ll * (a[i][j] - a[i][0]) + from_max);
    }
  }

  cout << dp[0][0] << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}