#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
  ll w, m, k;
  cin >> w >> m >> k;
  w /= k;

  ll took = 0;
  for (ll d = 1, got = 9; w >= d; d++, got *= 10) {
    ll L = got / 9;
    ll R = L + got - 1;
    if (R < m) continue;

    ll mx = w / d;
    ll take = min(R - max(m - 1, L - 1), mx);
    took += take;
    w -= take * d;
  }

  cout << took << endl;

  return 0;
}