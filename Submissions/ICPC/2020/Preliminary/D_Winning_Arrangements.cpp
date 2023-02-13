#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 1e9 + 7;

vector<int> solve(int n, vector<int> a) {
  map<int, vector<int>> me;
  for (int i = 0; i < n; i++) {
    me[a[i]].push_back(i);
  }

  int nn = me.size();
  vector<int> e, f;
  int pref = 0;
  for (auto [ve, ia] : me) {
    e.push_back(ve);
    f.push_back(pref += ia.size());
  }

  debug() << name(nn) name(e) name(f);

  vector<int> inv(n + 1), fact(n + 1), ifact(n + 1);
  inv[1] = fact[0] = ifact[0] = 1;
  for (int i = 2; i <= n; i++) inv[i] = (ll)inv[MOD % i] * (MOD - MOD / i) % MOD;
  for (int i = 1; i <= n; i++) fact[i] = (ll)fact[i - 1] * i % MOD;
  for (int i = 1; i <= n; i++) ifact[i] = (ll)ifact[i - 1] * inv[i] % MOD;

  vector<vector<int>> P(n + 1, vector<int>(n + 1, 0));
  for (int i = 0; i <= n; i++) {
    P[i][0] = 1;
    for (int j = 1; j <= i; j++) {
      P[i][j] = (ll)fact[i] * ifact[i - j] % MOD;
    }
  }

  // debug() << name(P);

  vector<vector<vector<int>>> dp(nn, vector<vector<int>>(nn, vector<int>(2, 0)));
  for (int at = nn - 1; ~at; at--) {
    for (int from = 0; from <= at; from++) {
      for (int side = 0; side < 2; side++) {
        debug() << name(at) name(from) name(side);
        int have;
        if (from == at) {
          have = f[at] - 1;
        } else {
          have = f[at - 1] - 1 - (e[at] - e[from]);
          if (have < 0) continue;
          have += f[at] - f[at - 1];
        }
        if (at != nn - 1 and have < e[at + 1] - e[at]) continue;
        int need = at == nn - 1 ? have : e[at + 1] - e[at];
        int eq = at == 0 ? f[at] : f[at] - f[at - 1];
        debug() << name(have) name(need);

        if (side == 0) {
          if (at == nn - 1) {
            dp[at][from][side] = fact[have + 1];
          } else {
            dp[at][from][side] = (ll)P[have][need] * dp[at + 1][from][side] % MOD;
            (dp[at][from][side] += (ll)P[have][need] * need % MOD * dp[at + 1][from][side ^ 1]) %= MOD;
          }
        } else {
          if (at == nn - 1) {
            dp[at][from][side] = (ll)fact[have] * (eq + 1) % MOD;
          } else {
            dp[at][from][side] = (ll)P[have][need] * dp[at + 1][from][side] % MOD;
            (dp[at][from][side] += (ll)eq * P[have - 1][need - 1] % MOD * need % MOD * dp[at + 1][from][side ^ 1]) %= MOD;
          }
        }
        debug() << name(dp[at][from][side]);
      }
    }
  }

  int ei = 0;
  vector<int> ans(n);
  for (auto [ve, ia] : me) {
    for (int i : ia) {
      ans[i] = dp[ei][ei][0];
    }
    ei++;
  }

  return ans;
}

int main() {
  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    int n;
    scanf("%d", &n);

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
      scanf("%d", &a[i]);
    }

    vector<int> ans = solve(n, a);
    printf("Case %d:\n", cs);
    for (int i : ans) printf("%d\n", i);
  }

  return 0;
}