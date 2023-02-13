#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 20;
int lsb[1 << N];

void init() {
  lsb[0] = -1;
  for (int mask = 1; mask < 1 << N; mask++) {
    lsb[mask] = __builtin_ctz(mask);
  }
}

void test_case() {
  int n;
  scanf("%d", &n);

  vector<vector<pair<int, bool>>> e(n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int r;
      char c;
      scanf(" (%d, %c)", &r, &c);
      e[i].push_back({r, c == 'T'});
    }
  }

  vector<vector<ll>> dp(1 << n, vector<ll>(n, 0));
  for (int mask = 1; mask < 1 << n; mask++) {
    int m1 = mask;
    while (m1) {
      int i1 = lsb[m1];
      m1 ^= 1 << i1;

      int m2 = m1;
      while (m2) {
        int i2 = lsb[m2];
        m2 ^= 1 << i2;

        int r = e[i2][i1].first;
        int i_stay = e[i2][i1].second ? i2 : i1;
        int i_rem = i1 + i2 - i_stay;
        ll curr = dp[mask ^ (1 << i_rem)][i_stay] + r;
        dp[mask][i1] = max(dp[mask][i1], curr);
        dp[mask][i2] = max(dp[mask][i2], curr);
      }
    }
  }

  ll ans = 0;
  for (int i = 0; i < n; i++) {
    ans = max(ans, dp[(1 << n) - 1][i]);
  }

  printf("%lld\n", ans);
}

int main() {
  init();

  int t;
  scanf("%d", &t);

  for (int cs = 1; cs <= t; cs++) {
    printf("Case %d: ", cs);
    test_case();
  }

  return 0;
}