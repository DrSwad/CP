#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n;
  cin >> n;

  ll tot = 0, mx_sum = 0;
  int mx = 0;
  while (n--) {
    int a, b;
    cin >> a >> b;
    tot += a + b;
    mx_sum += max(a, b);
    mx = max(mx, max(a, b));
  }

  cout << 2ll * tot - 2ll * (mx_sum - mx) << "\n";
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