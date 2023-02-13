#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  const int N = 10;
  typedef long long ll;
  int countSpecialNumbers(int n) {
    vector<vector<ll>> dp(N + 1, vector<ll>(N + 1, 0));
    for (int have = 0; have <= N; have++) {
      dp[have][0] = 1;
      for (int len = 1; len <= have; len++) {
        dp[have][len] = have * dp[have - 1][len - 1];
      }
    }

    string num = to_string(n);
    int sz = num.size();
    ll ans = 0;

    for (int len = 1; len < sz; len++) {
      ans += dp[N][len] - dp[N - 1][len - 1];
    }

    vector<bool> vis(N, false);
    for (int i = 0; i < sz; i++) {
      int d = num[i] - '0';

      for (int dd = i == 0 ? 1 : 0; dd < d; dd++) {
        if (vis[dd]) continue;
        ans += dp[N - i - 1][sz - i - 1];
      }

      if (vis[d]) break;
      vis[d] = true;

      if (i == sz - 1) ans++;
    }

    return ans;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cout << Solution().countSpecialNumbers(135) << "\n";

  return 0;
}