#include <bits/stdc++.h>
using namespace std;

const int N = 2005;
const int MOD = 998244353;

int n;
int freq[N];
int max_sum[N];
vector<vector<int>> dp[2];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  for (int i = 1; i <= n; i++) {
    int a;
    cin >> a;
    freq[a]++;
  }

  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      max_sum[k] += min(k, freq[i]);
    }
  }

  dp[0].resize(n + 1, vector<int>(n + 1, 0));
  for (int val = 0; val <= n; val++) dp[0][val][0] = 1;

  for (int k = 1; k <= n; k++) {
    int max_val = max_sum[k] / k;
    dp[1].resize(max_val + 1, vector<int>(n + 1, 0));

    for (int val = 0; val <= max_val and val < dp[0].size(); val++) {
      int max_rem_sum = max_sum[k] - val;
      for (int rem_sum = 0; rem_sum <= max_rem_sum; rem_sum++) {
        int &prv = dp[0][val][rem_sum];
        int &cur = dp[1][val][rem_sum + val];
        cur += prv;
        if (cur >= MOD) cur -= MOD;
      }
    }

    for (int val = max_val - 1; val >= 0; val--) {
      for (int sum = 0; sum <= max_sum[k]; sum++) {
        dp[1][val][sum] += dp[1][val + 1][sum];
        if (dp[1][val][sum] >= MOD) dp[1][val][sum] -= MOD;
      }
    }

    swap(dp[0], dp[1]);
    dp[1].clear();
  }

  cout << dp[0][0][n] << "\n";

  return 0;
}