#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int mod = 1e9 + 7;
const int N = 2e5 + 5;
const int A = 1024;

ll binExp(ll a, ll e, ll m = mod) {
  if (e == -1) e = m - 2;
  ll ret = 1;
  while (e) {
    if (e & 1) ret = ret * a % m;
    a = a * a % m, e >>= 1;
  }
  return ret;
}

const int inv1e4 = binExp(1e4, -1);
int n;
int a[N];
int p[N][2];
int dp[A];

void test_case() {
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  for (int i = 0; i < n; i++) {
    cin >> p[i][1];
    p[i][1] = 1ll * p[i][1] * inv1e4 % mod;
    p[i][0] = (1 - p[i][1] + mod) % mod;
  }

  memset(dp, 0, sizeof dp);
  dp[0] = 1;

  for (int i = 0; i < n; i++) {
    int new_dp[A];
    for (int new_xor = 0; new_xor < A; new_xor++) {
      new_dp[new_xor] = (1LL * dp[new_xor] * p[i][0] + 1LL * dp[new_xor ^ a[i]] * p[i][1]) % mod;
    }
    swap(dp, new_dp);
  }

  int ans = 0;
  for (int xr = 0; xr < A; xr++) {
    (ans += 1ll * dp[xr] * xr % mod * xr % mod) %= mod;
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}