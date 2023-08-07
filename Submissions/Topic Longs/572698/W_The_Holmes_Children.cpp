#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int mod = 1e9 + 7;

ll phi(ll n) {
  ll ret = 1;
  for (ll p = 2; p * p <= n; p++) {
    if (n % p == 0) {
      ll fact = 1;
      while (n % p == 0) {
        n /= p;
        fact *= p;
      }
      ret *= fact - fact / p;
    }
  }
  if (n > 1) ret *= n - 1;
  return ret;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ll n, k;
  cin >> n >> k;

  while (k and n > 1) {
    if (k & 1) n = phi(n);
    k--;
  }
  cout << n % mod << "\n";

  return 0;
}