#include <bits/stdc++.h>
using namespace std;

const int M = 2e6;
vector<int> divs[M + 1];

void test_case() {
  int n, m, k;
  cin >> n >> m >> k;

  vector<int> a(n);
  for (int &i : a) cin >> i;
  sort(a.begin(), a.end());

  vector<int> cost(m);
  for (int &i : cost) cin >> i;
  for (int i = m - 2; i >= 0; i--) {
    cost[i] = min(cost[i], cost[i + 1]);
  }

  vector<int> dp(2 * m + 1, INT_MAX);
  dp[1] = 0;
  for (int at = 2; at <= 2 * m; at++) {
    for (int d : divs[at]) {
      if (d <= m) {
        dp[at] = min(dp[at], dp[at / d] + cost[d - 1]);
      }
    }
  }
  for (int at = 2 * m - 1; at >= 1; at--) {
    dp[at] = min(dp[at], dp[at + 1]);
  }

  function<bool(int)> check =
    [&](int median) {
      long long tot_cost = 0;
      for (int i = 0; i <= n / 2; i++) {
        if (a[i] > median) {
          int need = a[i] / (median + 1) + 1;
          tot_cost += dp[need];
        }
      }
      return tot_cost <= k;
    };

  int L = -1, R = m;
  while (R - L > 1) {
    int mid = (L + R) / 2;
    if (check(mid)) R = mid;
    else L = mid;
  }

  cout << R << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  for (int d = 2; d <= M; d++) {
    for (int m = d; m <= M; m += d) {
      divs[m].push_back(d);
    }
  }

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}