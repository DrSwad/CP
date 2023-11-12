#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll get_sum(int n, int terms) {
  int m = n - terms;
  return 1ll * n * (n + 1) / 2 - 1ll * m * (m + 1) / 2;
}

void test_case() {
  int n, x, y;
  cin >> n >> x >> y;

  ll dx = n / x - n / (1ll * x * y / gcd(x, y));
  ll dy = n / y - n / (1ll * x * y / gcd(x, y));

  ll ans = get_sum(n, dx) - get_sum(dy, dy);
  cout << ans << "\n";
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