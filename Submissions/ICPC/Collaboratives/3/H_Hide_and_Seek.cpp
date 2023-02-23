#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

map<long long, int> brute(int d01, int d02) {
  vector<pair<long long, long long>> cells1, cells2;

  for (int i = 0; i <= d01; i++) {
    cells1.emplace_back(i, d01 - i);
    cells1.emplace_back(i, i - d01);
    cells1.emplace_back(-i, d01 - i);
    cells1.emplace_back(-i, i - d01);
  }

  for (int i = 0; i <= d02; i++) {
    cells2.emplace_back(i, d02 - i);
    cells2.emplace_back(i, i - d02);
    cells2.emplace_back(-i, d02 - i);
    cells2.emplace_back(-i, i - d02);
  }

  sort(cells1.begin(), cells1.end());
  cells1.resize(
      unique(cells1.begin(), cells1.end()) - cells1.begin());
  sort(cells2.begin(), cells2.end());
  cells2.resize(
      unique(cells2.begin(), cells2.end()) - cells2.begin());
  // debug() << name(cells1);
  // debug() << name(cells2);

  map<long long, int> distFreq;
  for (auto [x1, y1] : cells1) {
    for (auto [x2, y2] : cells2) {
      long long dist = abs(x2 - x1) + abs(y2 - y1);
      distFreq[dist]++;
    }
  }

  return distFreq;
}

ll solve(ll d01, ll x) {
  ll d02 = d01;
  ll a = 4 * d01;

  if (x == 0) { return a; }
  if (d01 == 1) { return 12; }

  a += (4 * (d01 + 2));
  x--;
  if (x == 0) { return a; }

  if (x <= d01 - 2) { return a + x * 8; }
  a += (d01 - 2) * 8;
  a += 4 * ((d01 - 1) * (d01 - 1) + 1);
  return a;
}

ll solve(ll d01, ll d02, ll d12) {
  if (d01 > d02) { swap(d01, d02); }

  if (d01 == 0) {
    if (d02 != d12) {
      return 0;
    } else if (d02 == 0) {
      return 1;
    } else {
      return 4 * d02;
    }
  } else if (d12 == 0) {
    if (d01 == d02) {
      return 4 * d01;
    } else {
      return 0;
    }
  } else {
    if ((d01 + d12 - d02) % 2 != 0) { return 0; }
    ll x = (d01 + d12 - d02) / 2;
    if (x < 0 or x > d01) { return 0; }
    ll y = d02 - d01;

    ll a = solve(d01, x);
    // debug() << name(x) name(y) name(a);
    ll period = x == 0 or x == d01 ? 4 * (d01 + 1) : 8;
    return a + period * y;
  }
}

int main() {
  // for (int d01 = 0; d01 <= 10; d01++) {
  //   for (int d02 = d01; d02 <= 10; d02++) {
  //     // debug() << name(d01) name(d02) name(brute(d01, d02));
  //     for (auto [d12, freq] : brute(d01, d02)) {
  //       if (solve(d01, d02, d12) != freq) {
  //         debug() << name(d01) name(d02) name(d12) name(freq)
  //                 name(solve(d01, d02, d12));
  //       }
  //     }
  //   }
  //   // cerr << endl;
  // }

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    printf("Case #%d: ", cs);

    ll d01, d02, d12;
    scanf("%lld %lld %lld", &d01, &d02, &d12);
    printf("%lld\n", solve(d01, d02, d12));
  }

  return 0;
}