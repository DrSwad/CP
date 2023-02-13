#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  ll a, b, c, d;
  cin >> a >> b >> c >> d;

  if (a * d == b * c) {
    cout << "0\n";
    return;
  }

  auto check = [](ll a, ll b, ll c, ll d) {
    if (a == 0) return true;
    return c * b % d == 0 and c * b / d % a == 0;
  };

  if (check(a, b, c, d) or check(c, d, a, b) or check(a, c, b, d) or check(b, d, a, c)) {
    cout << "1\n";
    return;
  }

  cout << "2\n";
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