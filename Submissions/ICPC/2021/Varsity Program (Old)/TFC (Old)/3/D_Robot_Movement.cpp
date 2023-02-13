#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

void test_case() {
  int n;
  cin >> n;

  int x1, y1;
  cin >> x1 >> y1;
  int x2, y2;
  cin >> x2 >> y2;

  if (x1 == x2) {
    cout << abs(y2 - y1) + 1 << "\n";
    return;
  }

  n = 2 * n + 1;
  x1 = x1 * 2 + 1, y1 = 2 * y1 + 1;
  x2 = x2 * 2 + 1, y2 = 2 * y2 + 1;
  if (x1 > x2) swap(x1, x2);
  if (y1 > y2) swap(y1, y2);
  // debug(n, x1, y1, x2, y2);

  auto intersect = [&](int x) {
    if (x > x2) return (ll)y2;
    if (x < x1) return (ll)y1;

    // (y - y1) / (x - x1) = (y2 - y1) / (x2 - x1)
    // (y - y1) = (y2 - y1) * (x - x1) / (x2 - x1)
    ll numerator = (y2 - y1) * (x - x1);
    ll denominator = (x2 - x1);

    if (numerator % denominator == 0) {
      return numerator / denominator + y1;
    }
    else {
      ld ret = (ld)numerator / denominator + y1;
      ll _ret = ret;
      return _ret % 2 == 1 ? _ret : _ret + 1;
    }
  };

  ll ans = 0;
  for (int x = x1 - 1; x < x2; x += 2) {
    ll st = intersect(x), en = intersect(x + 2);
    // debug(x, st, en);
    assert(en >= st);
    st = (st - 1) / 2;
    en = (en + 2) / 2;
    ans += (en - st);
    // debug(ans);
  }
  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}