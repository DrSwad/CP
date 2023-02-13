#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n, m, k;
  cin >> n >> m >> k;

  vector<int> x(n), y(m);
  for (int &i : x) cin >> i;
  for (int &i : y) cin >> i;

  vector<map<int, int>> vmpx(n), vmpy(m);

  while (k--) {
    int cx, cy;
    cin >> cx >> cy;

    bool hx = binary_search(x.begin(), x.end(), cx);
    bool hy = binary_search(y.begin(), y.end(), cy);

    int ix = lower_bound(x.begin(), x.end(), cx) - x.begin();
    int iy = lower_bound(y.begin(), y.end(), cy) - y.begin();

    if (hx and hy) continue;
    else if (hx) vmpy[iy][ix]++;
    else if (hy) vmpx[ix][iy]++;
  }

  ll ans = 0;

  for (auto mpx : vmpx) {
    ll tot = 0;
    for (auto [y, f] : mpx) tot += f;
    ans += tot * tot;
    for (auto [y, f] : mpx) ans -= f * f;
  }
  for (auto mpy : vmpy) {
    ll tot = 0;
    for (auto [x, f] : mpy) tot += f;
    ans += tot * tot;
    for (auto [x, f] : mpy) ans -= f * f;
  }

  ans /= 2;
  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t;
  cin >> t;

  while (t--) {
    test_case();
  }

  return 0;
}