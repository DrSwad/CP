#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 4e5 + 5;
const int MOD = 1e9 + 7;

int n;
int a[N];
int inv[N], fact[N], ifact[N];

void init() {
  inv[1] = fact[0] = ifact[0] = 1;
  for (int i = 2; i < N; i++) inv[i] = (ll)inv[MOD % i] * (MOD - MOD / i) % MOD;
  for (int i = 1; i < N; i++) fact[i] = (ll)fact[i - 1] * i % MOD;
  for (int i = 1; i < N; i++) ifact[i] = (ll)ifact[i - 1] * inv[i] % MOD;
}

int nCk(int n, int k) {
  if (k<0 or k> n) return 0;
  if (k == 0 or k == n) return 1;
  return (ll)fact[n] * ifact[k] % MOD * ifact[n - k] % MOD;
}

int hockey_stick(int r, int n) {
  if (r == 0) return n;
  return nCk(r + n, r + 1);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  init();

  cin >> n;
  for (int i = 0; i <= n; i++) {
    cin >> a[i];
  }

  int ans = 0;
  for (int i = 0; i <= n; i++) {
    (ans += hockey_stick(i, a[i])) %= MOD;
  }

  cout << ans << "\n";

  return 0;
}