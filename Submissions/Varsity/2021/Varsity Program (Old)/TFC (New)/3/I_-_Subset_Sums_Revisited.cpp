#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int P = 61;
const int N = 102;
const int MOD = 1e9 + 7;

ll nCk[N][N];
void init() {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j <= i; j++) {
      if (j == 0 or j == i) nCk[i][j] = 1;
      else nCk[i][j] = (nCk[i - 1][j] + nCk[i - 1][j - 1]) % MOD;
    }
  }
}

void test_case() {
  int n;
  ll k;
  cin >> n >> k;

  vector<int> a(n), p_freq(P + 1, 0);
  for (int &i : a) cin >> i, p_freq[i]++;

  vector<vector<ll>> dp(P + 1, vector<ll>(N, 0));
  dp[P][0] = 1;

  for (int p = P - 1; p >= 0; p--) {
    for (int carry = 0; carry <= n; carry++) {
      int tot_p = p_freq[p] + carry;
      if (tot_p > n) break;

      for (int take = (k >> p & 1) == (carry & 1) ? carry : carry + 1; take <= tot_p; take += 2) {
        dp[p][carry] += nCk[p_freq[p]][take - carry] * dp[p + 1][take / 2] % MOD;
        if (dp[p][carry] >= MOD) dp[p][carry] -= MOD;
      }
    }
  }

  cout << dp[0][0] << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  init();

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}