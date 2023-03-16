#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ll r, e;
  cin >> r >> e;

  if (r % e != 0 or e == 1) cout << "0\n";
  else {
    ll phi = 1;

    for (int p = 2; 1ll * p * p <= e; p++) {
      if (e % p == 0) {
        ll prv_fact = 1;
        ll fact = p;
        e /= p;
        while (e % p == 0) {
          prv_fact = fact;
          fact *= p;
          e /= p;
        }
        phi *= (fact - prv_fact);
      }
    }
    if (e > 1) phi *= (e - 1);

    cout << phi << "\n";
  }

  return 0;
}
