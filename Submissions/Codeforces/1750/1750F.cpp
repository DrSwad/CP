#include <bits/stdc++.h>
using namespace std;

const int N = 5e3 + 5;

int n, m;
int dp[N][N], dp2[N][N], dp_pref[N][N], dp_pref_stair[N][N];
int ans[N];
int pow2[N];

int add(int a, int b) {
  int c = a + b;
  return c >= m ? c - m : c;
}

int mul(int a, int b) {
  return 1ll * a * b % m;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;

  pow2[0] = 1;
  for (int i = 1; i <= n; i++) {
    pow2[i] = mul(pow2[i - 1], 2);
  }

  ans[1] = 1;
  dp2[1][1] = 1;
  for (int i = 1; i <= n; i++) {
    dp_pref[1][i] = add(dp_pref[1][i - 1], dp2[1][i]);
    dp_pref_stair[1][i] = dp_pref[1][i];
  }

  for (int len = 2; len <= n; len++) {
    for (int pref = 1; pref < len; pref++) {
      int len2 = len - 2 * pref - 2;
      if (len2 >= 1) {
        dp[len][pref] = mul(ans[pref], dp_pref_stair[len2][1]);
      }

      dp2[len][pref] = add(dp[len][pref], ans[pref]);

      dp_pref[len][pref] = add(dp_pref[len][pref - 1], dp2[len][pref]);
    }

    ans[len] = add(pow2[len - 1], m - dp_pref[len][len - 1]);

    dp2[len][len] = ans[len];

    for (int pref = len; pref <= n; pref++) {
      dp_pref[len][pref] = add(dp_pref[len][pref - 1], dp2[len][pref]);
    }

    for (int pref = 1; pref <= n; pref++) {
      dp_pref_stair[len][pref] = add(dp_pref[len][pref], dp_pref_stair[len - 1][min(pref + 1, n)]);
    }
  }

  cout << ans[n] << "\n";

  return 0;
}