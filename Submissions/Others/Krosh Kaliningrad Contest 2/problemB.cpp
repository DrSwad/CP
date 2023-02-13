#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 4e5 + 5;
const int MOD = 1e9 + 7;

int fact[N], inv[N], ifact[N];

void init() {
  inv[1] = fact[0] = ifact[0] = 1;
  for (int i = 2; i < N; i++) inv[i] = (ll)inv[MOD % i] * (MOD - MOD / i) % MOD;
  for (int i = 1; i < N; i++) fact[i] = (ll)fact[i - 1] * i % MOD;
  for (int i = 1; i < N; i++) ifact[i] = (ll)ifact[i - 1] * inv[i] % MOD;
}

int nCk(int n, int k) {
  if (k < 0 or k > n) return 0;
  return (ll)fact[n] * ifact[k] % MOD * ifact[n - k] % MOD;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  init();

  int n, k;
  cin >> n >> k;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  int ans = 0;
  for (int i = 0; i < n; i++) {
    (ans += (ll)a[i] * nCk(i + k, k) % MOD * nCk(n - 1 - i + k, k) % MOD) %= MOD;
  }

  cout << ans << "\n";
  
  return 0;
}