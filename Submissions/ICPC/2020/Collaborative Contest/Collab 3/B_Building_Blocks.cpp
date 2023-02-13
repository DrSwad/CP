#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e5 + 5;
const int MOD = 1e9 + 7;

int n, m, k;
vector<int> a;
vector<int> freqH;
vector<bool> isDone;
vector<vector<ll>> dp;

ll binExp(ll a, ll e, ll m = MOD) {
  if (e == -1) { e = m - 2; }
  ll ret = 1;
  while (e) {
    if (e & 1) { ret = ret * a % m; }
    a = a * a % m, e >>= 1;
  }
  return ret;
}

ll DP(int at, bool currDone) {
  if (dp[at][currDone] != -1) return dp[at][currDone];
  if (at == n + m - 1) return dp[at][currDone] = 1;
  // debug() << name(at) name(currDone);

  int cap = min(at + 1, min(n + m - 1 - at, min(n, m)));
  // debug() << name(cap) name(freqH[at]);
  if (freqH[at] == cap) {
    if (!currDone and !isDone[at]) return dp[at][currDone] = 0;
    else
      return dp[at][currDone] = DP(at + 1, isDone[at + 1]);
  }

  if (at == n + m - 1) return dp[at][currDone] = 1;

  int rem = cap - freqH[at];
  ll &ret = dp[at][currDone];
  ret = 0;

  if (currDone) {
    if (isDone[at + 1]) {
      ret =
          binExp(min(a[at], a[at + 1]), rem) * DP(at + 1, true) % MOD;
    } else {
      ret = binExp(min(a[at + 1] - 1, a[at]), rem) * DP(at + 1, false)
          % MOD;
      if (a[at] >= a[at + 1]) {
        (ret += (binExp(a[at + 1], rem) - binExp(a[at + 1] - 1, rem)
                    + MOD)
                % MOD * DP(at + 1, true) % MOD) %= MOD;
      }
    }
  } else {
    if (a[at] > a[at + 1]) ret = 0;
    else {
      ret = (binExp(a[at], rem) - binExp(a[at] - 1, rem) + MOD) % MOD
          * DP(at + 1, a[at] == a[at + 1] or isDone[at + 1]) % MOD;
    }
  }

  return ret;
}

int main() {
  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    printf("Case #%d: ", cs);

    scanf("%d %d %d", &n, &m, &k);
    a = vector<int>(n + m);
    freqH = vector<int>(n + m - 1, 0);
    isDone = vector<bool>(n + m, false);
    dp = vector<vector<ll>>(n + m, vector<ll>(2, -1));

    for (int i = 0; i < n + m; i++) scanf("%d", &a[i]);

    bool flag = false;
    for (int i = 0; i < k; i++) {
      int x, y, h;
      scanf("%d %d %d", &x, &y, &h);
      x--, y--;

      freqH[x + y]++;
      if (h > a[x + y] or h > a[x + y + 1]) {
        flag = true;
      } else {
        if (h == a[x + y]) isDone[x + y] = true;
        if (h == a[x + y + 1]) isDone[x + y + 1] = true;
      }
    }

    if (freqH[n + m - 2] == 0) {
      freqH[n + m - 2] = 1;
      isDone[n + m - 1] = true;
      if (a[n + m - 1] == a[n + m - 2]) isDone[n + m - 2] = true;
    } else if (!isDone[n + m - 1])
      flag = true;

    printf("%lld\n", flag ? 0 : DP(0, isDone[0]));
    // debug() << name(dp);
  }

  return 0;
}