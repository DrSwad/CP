#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int B, y;
  cin >> B >> y;

  function<ll(int)> cost =
    [&](int m) {
      int l = m / 2;
      int r = m - l;
      return 1ll * l * l + 1ll * r * r + 1ll * m * y;
    };

  int m = 0;
  while (cost(m + 1) <= B) m++;

  cout << (1ll << m) << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}