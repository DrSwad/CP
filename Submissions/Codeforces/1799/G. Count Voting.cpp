#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int mod = 998244353;

int add(int a, int b) {
  int c = a + b;
  return c < mod ? c : c - mod;
}

int mul(int a, int b) {
  return 1ll * a * b % mod;
}

ll binExp(ll a, ll e, ll m = mod) {
  if (e == -1) e = m - 2;
  ll ret = 1;
  while (e) {
    if (e & 1) ret = ret * a % m;
    a = a * a % m, e >>= 1;
  }
  return ret;
}

const int N = 205;

int n;
int c[N], t[N];
int tc[N], tv[N];
int fact[N], ifact[N];
int C[N][N];
int dp[N][N][N];

void init() {
  fact[0] = 1;
  for (int i = 1; i < N; i++) {
    fact[i] = mul(fact[i - 1], i);
  }

  ifact[N - 1] = binExp(fact[N - 1], -1);
  for (int i = N - 2; i >= 0; i--) {
    ifact[i] = mul(ifact[i + 1], i + 1);
  }

  for (int n = 0; n < N; n++) {
    for (int k = 0; k <= n; k++) {
      C[n][k] = mul(fact[n], mul(ifact[k], ifact[n - k]));
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  init();

  cin >> n;
  for (int i = 1; i <= n; i++) cin >> c[i];
  for (int i = 1; i <= n; i++) cin >> t[i];
  for (int i = 1; i <= n; i++) tc[t[i]] += c[i], tv[t[i]]++;

  dp[0][0][0] = 1;

  for (int t = 1, pc = 0, pv = 0; t <= n; t++) {
    for (int cc = max(0, pc - pv); cc <= pc; cc++) {
      int cv = pv - (pc - cc);
      
      for (int uc = 0; uc <= min(tc[t], cv); uc++) {
        for (int uv = 0; uv <= min(tv[t], cc); uv++) {
          int nc = cc - uv + tc[t] - uc;
          int nv = cv - uc + tv[t] - uv;
          int wc = mul(mul(C[tc[t]][uc], C[cv][uc]), fact[uc]);
          int wv = mul(mul(C[tv[t]][uv], C[cc][uv]), fact[uv]);
          dp[t][nc][nv] = add(dp[t][nc][nv], mul(dp[t - 1][cc][cv], mul(wc, wv)));
        }
      }
    }

    pc += tc[t];
    pv += tv[t];
  }

  int ans = dp[n][0][0];
  for (int i = 1; i <= n; i++) {
    ans = mul(ans, ifact[c[i]]);
  }

  cout << ans << "\n";

  return 0;
}
