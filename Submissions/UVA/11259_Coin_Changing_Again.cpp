#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e5 + 3;
const ll MOD = 1e18;

const int n = 4;
int q;
int c[n], d[n], v;
ll dp[N];

void add(ll &a, const ll &b) {
  a += b;
  if (a >= MOD) a -= MOD;
}

void query_case() {
  for (int i = 0; i < n; i++) cin >> d[i];
  cin >> v;

  ll ans = dp[v];

  for (int mask = 1; mask < 1 << n; mask++) {
    ll nv = v;
    for (int i = 0; i < n; i++) {
      if (mask >> i & 1) {
        nv -= 1ll * (d[i] + 1) * c[i];
      }
    }
    if (nv < 0) continue;

    int b = __builtin_popcount(mask);
    ll inc = b % 2 == 0 ? dp[nv] : dp[nv] == 0 ? dp[nv] : MOD - dp[nv];
    add(ans, inc);
  }

  cout << ans << "\n";
}

void test_case() {
  for (int i = 0; i < n; i++) cin >> c[i];

  memset(dp, 0, sizeof dp);
  dp[0] = 1;

  for (int i = 0; i < n; i++) {
    for (int sum = 0; sum < N; sum++) {
      if (sum >= c[i]) {
        add(dp[sum], dp[sum - c[i]]);
      }
    }
  }

  cin >> q;
  while (q--) {
    query_case();
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t;
  cin >> t;
  while (t--) test_case();

  return 0;
}