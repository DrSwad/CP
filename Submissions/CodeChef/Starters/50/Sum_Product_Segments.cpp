#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  ll x, y;
  cin >> x >> y;

  ll xl = x / 2;
  ll xr = (x + 1) / 2;

  ll yl, yr;
  for (ll d = 1; d * d <= y; d++) {
    if (y % d == 0) {
      yl = d;
      yr = y / d;
    }
  }

  if (xr < yl or yr < xl) {
    cout << xl << " " << xr << "\n";
    cout << yl << " " << yr << "\n";
  }
  else cout << "-1\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}