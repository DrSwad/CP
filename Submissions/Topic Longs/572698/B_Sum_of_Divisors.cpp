#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int mod = 1e9 + 7;
const int inv2 = (mod + 1) / 2;

int add(int a, int b) {
  int c = a + b;
  return c < mod ? c : c - mod;
}

int mul(int a, int b) {
  return 1ll * a * b % mod;
}

int sum(ll a) {
  if (a >= mod) a %= mod;
  return a * (a + 1) % mod * inv2 % mod;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ll n;
  cin >> n;

  ll ans = 0;
  for (ll l = 1; l <= n; ) {
    ll r = n / (n / l);
    ans = add(ans, mul(n / l % mod, add(sum(r), mod - sum(l - 1))));
    l = r + 1;
  }

  cout << ans << "\n";

  return 0;
}