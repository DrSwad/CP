#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
  ll L;
  cin >> L;

  ll a, b;
  ll mn = L + 1;
  for (ll i = 1; i <= 1e6; i++) {
    if (L % i == 0) {
      ll j = L / i;
      if (gcd(i, j) == 1 and max(i, j) < mn) {
        a = i, b = j, mn = max(i, j);
      }
    }
  }

  cout << a << " " << b << endl;

  return 0;
}