#include <bits/stdc++.h>
using namespace std;

void test_case() {
  string n;
  cin >> n;

  int d;
  cin >> d;

  vector<long long> dp(2);
  dp[0] = 0, dp[1] = -1;

  reverse(n.begin(), n.end());
  long long p = 1;

  for (char c : n) {
    int ad = c - '0';
    vector<long long> ndp(2, -1);

    for (int carry = 0; carry < 2; carry++) {
      if (dp[carry] == -1) continue;

      for (int cd = 0; cd < 10; cd++) {
        int nd = ad + cd + carry;
        int ncarry = nd >= 10;
        if (nd >= 10) nd -= 10;
        if (nd == d) continue;

        long long curr = cd * p + dp[carry];
        long long &ans = ndp[ncarry];
        ans = ans == -1 ? curr : min(ans, curr);
      }
    }

    swap(ndp, dp);
    p *= 10;
  }

  long long ans = dp[0];
  if (dp[1] != -1 and d != -1) ans = ans == -1 ? dp[1] : min(ans, dp[1]);
  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}