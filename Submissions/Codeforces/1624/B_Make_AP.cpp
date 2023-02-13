#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  ll a, b, c;
  cin >> a >> b >> c;

  bool ans = false;

  ll nc = 2 * b - a;
  if (nc >= c and nc % c == 0) ans = true;

  ll na = 2 * b - c;
  if (na >= a and na % a == 0) ans = true;

  if (a % 2 == c % 2) {
    ll nb = (a + c) / 2;
    if (nb >= b and nb % b == 0) ans = true;
  }

  cout << (ans ? "YES" : "NO") << "\n";
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