#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pcc pair<char, char>
#define vi vector<int>
#define vl vector<ll>
using namespace std;
ll powmod(ll base, ll exponent, ll mod) {
  ll ans = 1;
  if (base < 0) base += mod;
  while (exponent) {
    if (exponent & 1) ans = (ans * base) % mod;
    base = (base * base) % mod;
    exponent /= 2;
  }
  return ans;
}
const int N = 201;
const int mod = 998244353;
int fact[N];
int invfact[N];
int nCr(int n, int r) {
  int ans = fact[n];
  ans = (1ll * ans * invfact[r]) % mod;
  ans = (1ll * ans * invfact[n - r]) % mod;
  return ans;
}
int interpolate(vi &y, int r, int n) {
  int ans = 0, prod = 1, temp;
  for (int i = 1; i <= r; i++) {
    prod = (1ll * prod * (n - i)) % mod;
  }
  for (int i = 0; i < r; i++) {
    temp = (1ll * prod * powmod(n - i - 1, mod - 2, mod)) % mod;
    temp = (1ll * temp * y[i]) % mod;
    temp = (1ll * temp * invfact[i]) % mod;
    temp = (1ll * temp * invfact[r - i - 1]) % mod;
    if ((r - i) % 2 == 0) temp = mod - temp;
    ans += temp; ans %= mod;
  }
  return ans;
}
void brute_force(int n, int k) {
  vi values_of_polynomial(k);
  for (int i = 1; i <= n; i++) {
    for (int x = 0; x < i; x++) {
      for (int y = x + 1; y <= n - i; y++) {
        for (int val = 1; val <= k; val++) {
          ll calculation = (1ll * nCr(i - 1, x) * powmod(val - 1, x, mod)) % mod;
          calculation *= powmod(k + 1 - val, i - 1 - x, mod);
          calculation %= mod;
          calculation *= (1ll * nCr(n - i, y) * powmod(k - val, y, mod)) % mod;
          calculation %= mod;
          calculation *= powmod(val, n - i - y, mod);
          calculation %= mod;
          calculation *= val;
          calculation %= mod;
          values_of_polynomial[val - 1] += calculation;
          values_of_polynomial[val - 1] %= mod;
        }
      }
    }
  }
  for (int i = 1; i < k; i++) {
    values_of_polynomial[i] += values_of_polynomial[i - 1];
    values_of_polynomial[i] %= mod;
  }
  cout << values_of_polynomial[k - 1] << "\n";
}
int main() {
  fact[0] = 1;
  invfact[0] = 1;
  for (int i = 1; i < N; i++) {
    fact[i] = (1ll * i * fact[i - 1]) % mod;
    invfact[i] = powmod(fact[i], mod - 2, mod);
  }
  int t, n, k;
  t = 1;
  while (t--) {
    cin >> n >> k;
    vi values_of_polynomial(n + 3, 0);
    for (int i = 1; i <= n; i++) {
      for (int x = 0; x < i; x++) {
        for (int y = x + 1; y <= n - i; y++) {
          for (int val = 1; val <= n + 3; val++) {
            ll calculation = (1ll * nCr(i - 1, x) * powmod(val - 1, x, mod)) % mod;
            calculation *= powmod(k + 1 - val, i - 1 - x, mod);
            calculation %= mod;
            calculation *= (1ll * nCr(n - i, y) * powmod(k - val, y, mod)) % mod;
            calculation %= mod;
            calculation *= powmod(val, n - i - y, mod);
            calculation %= mod;
            calculation *= val;
            calculation %= mod;
            values_of_polynomial[val - 1] += calculation;
            values_of_polynomial[val - 1] %= mod;
          }
        }
      }
    }
    for (int i = 1; i < n + 3; i++) {
      values_of_polynomial[i] += values_of_polynomial[i - 1];
      values_of_polynomial[i] %= mod;
    }
    debug(values_of_polynomial);
    if (k <= n + 3) cout << values_of_polynomial[k - 1] << "\n";
    else cout << interpolate(values_of_polynomial, n + 3, k) << "\n";
  }
  return 0;
}