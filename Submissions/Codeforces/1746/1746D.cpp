#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n, k;
  cin >> n >> k;

  vector<vector<int>> e(n);
  for (int i = 1; i < n; i++) {
    int p;
    cin >> p;
    p--;
    e[p].push_back(i);
  }

  vector<int> s(n);
  for (int &i : s) cin >> i;

  vector<unordered_map<int, ll>> dp(n);
  function<ll(int, int)> DP = [&](int at, int k) {
    if (dp[at].count(k)) return dp[at][k];
    dp[at][k] = 1ll * s[at] * k;
    if (e[at].empty()) return dp[at][k];

    vector<ll> ch_dps;
    int ch_cnt = e[at].size();
    int ch_k = k / ch_cnt, rem = k % ch_cnt;

    for (int ch : e[at]) {
      ll ch_dp = DP(ch, ch_k);
      dp[at][k] += ch_dp;
      if (rem) {
        ch_dps.push_back(DP(ch, ch_k + 1) - ch_dp);
      }
    }

    if (rem) {
      int sz = e[at].size();
      nth_element(ch_dps.begin(), ch_dps.begin() + (rem - 1), ch_dps.end(), greater<ll>());
      for (int i = 0; i < rem; i++) {
        dp[at][k] += ch_dps[i];
      }
    }

    return dp[at][k];
  };

  cout << DP(0, k) << "\n";
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