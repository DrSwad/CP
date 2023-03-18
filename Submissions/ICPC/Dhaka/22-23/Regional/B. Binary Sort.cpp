#include <bits/stdc++.h>
using namespace std;

const int BITS = 60;
const int INF = 1e9;
typedef long long ll;

void test_case() {
  int n;
  cin >> n;

  vector<ll> a(n);
  for (ll &i : a) cin >> i;

  vector pref(BITS, vector(n + 1, 0));
  for (int bit = 0; bit < BITS; bit++) {
    for (int i = 0; i < n; i++) {
      pref[bit][i + 1] = pref[bit][i] + (a[i] >> bit & 1);
    }
  }

  vector dp(2, vector(n, vector(n, 0)));
  vector opt(2, vector(n, vector(n, -1)));

  for (int bit = 0; bit < BITS; bit++) {
    int b = bit & 1;

    for (int i = 0; i < n; i++) {
      dp[b][i][i] = 0;
      if (a[i] >> bit & 1) opt[b][i][i] = i;
      else opt[b][i][i] = i - 1;
    }

    for (int i = n - 1; i >= 0; i--) {
      for (int j = i + 1; j < n; j++) {
        dp[b][i][j] = INF;

        for (int k = max(i - 1, opt[b][i][j - 1]); k <= min(j, opt[b][i + 1][j]); k++) {
          int b1 = b ^ 1;
          if ((k >= i and dp[b1][i][k] == -1) or (k < j and dp[b1][k + 1][j] == -1)) continue;
          if (pref[bit][k + 1] - pref[bit][i] > 0) continue;
          int cost = (j - k) - (pref[bit][j + 1] - pref[bit][k + 1]);
          int cur = (k >= i ? dp[b1][i][k] : 0) + (k < j ? dp[b1][k + 1][j] : 0) + cost;
          if (cur < dp[b][i][j]) {
            dp[b][i][j] = cur;
            opt[b][i][j] = k;
          }
        }
      }
    }
  }

  cout << dp[(BITS - 1) & 1][0][n - 1] << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}
