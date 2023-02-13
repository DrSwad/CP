#include <bits/stdc++.h>
using namespace std;

const int N = 20;

int n;
string s[N];
int mn[N];
int dp[1 << N], sum[1 << N];
map<int, int> mp[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> s[i];

    int &tot = sum[1 << i];
    for (char c : s[i]) {
      tot += c == '(' ? 1 : -1;
      if (mp[i].empty() or tot <= mp[i].begin()->first) mp[i][tot]++;
    }
    mn[i] = mp[i].begin()->first;
  }

  int ans = 0;
  for (int mask = 1; mask < 1 << n; mask++) {
    dp[mask] = -1;
    for (int i = 0; i < n; i++) {
      if (mask >> i & 1) {
        int nmask = mask ^ (1 << i);
        sum[mask] = sum[nmask] + sum[1 << i];

        if (~dp[nmask]) {
          int curr = dp[nmask] + (mp[i].find(-sum[nmask]) == mp[i].end() ? 0 : mp[i][-sum[nmask]]);
          ans = max(ans, curr);

          if (sum[nmask] + mn[i] >= 0) {
            dp[mask] = max(dp[mask], curr);
          }
        }
      }
    }
  }

  cout << ans << "\n";

  return 0;
}