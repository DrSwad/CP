#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 15;

int n;
ll c[2][N];
ll p[N];
ll dp1[2][1 << N][N];
ll dp2[2][1 << N][N + 1];
ll dp3[1 << N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> c[0][i] >> c[1][i] >> p[i];
  }

  for (int ci = 0; ci < 2; ci++) {
    for (int lines = 0; lines < 1 << n; lines++) {
      for (int i = 0; i < n; i++) {
        ll &ans = dp1[ci][lines][i];
        ans = abs(c[ci][i]);

        for (int j = 0; j < n; j++) {
          if (lines >> j & 1) {
            ans = min(ans, (ll)abs(c[ci][j] - c[ci][i]));
          }
        }

        ans *= p[i];
      }
    }
  }

  for (int ci = 0; ci < 2; ci++) {
    for (int points = 0; points < 1 << n; points++) {
      for (int sz = 0; sz <= n; sz++) {
        dp2[ci][points][sz] = LLONG_MAX;
      }
    }
  }

  for (int ci = 0; ci < 2; ci++) {
    for (int lines = 0; lines < 1 << n; lines++) {
      int bits = __builtin_popcount(lines);
      dp3[lines] = 0;
      for (int i = 0; i < n; i++) {
        if (lines >> i & 1) {
          dp3[lines] += dp1[ci][lines][i];
        }
      }
      dp2[ci][lines][bits] = min(dp2[ci][lines][bits], dp3[lines]);

      for (int points = lines | (lines + 1); points < 1 << n; points = lines | (points + 1)) {
        int lsb = __builtin_ctz(points - lines);
        dp3[points] = dp3[points - (1 << lsb)] + dp1[ci][lines][lsb];
        dp2[ci][points][bits] = min(dp2[ci][points][bits], dp3[points]);
      }
    }
  }

  for (int ci = 0; ci < 2; ci++) {
    for (int points = 0; points < 1 << n; points++) {
      for (int sz = 1; sz <= n; sz++) {
        dp2[ci][points][sz] = min(dp2[ci][points][sz - 1], dp2[ci][points][sz]);
      }
    }
  }

  for (int k = 0; k <= n; k++) {
    ll ans = LLONG_MAX;
    for (int points0 = 0; points0 < 1 << n; points0++) {
      int points1 = ((1 << n) - 1) - points0;
      for (int s0 = 0; s0 <= k; s0++) {
        int s1 = k - s0;
        ans = min(ans, dp2[0][points0][s0] + dp2[1][points1][s1]);
      }
    }

    cout << ans << "\n";
  }

  return 0;
}