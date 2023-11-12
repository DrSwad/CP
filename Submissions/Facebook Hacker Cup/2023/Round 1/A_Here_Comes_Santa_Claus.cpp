#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n;
  cin >> n;

  vector<ll> x(n);
  for (ll &i : x) cin >> i;

  sort(x.begin(), x.end());

  double ans = 0;

  if (n == 5) {
    ans = max(
      abs(x[n - 1] + x[n - 2] - x[n - 3] - x[0]) / 2.0,
      abs(x[n - 1] + x[n - 3] - x[0] - x[1]) / 2.0
    );
  }
  else {
    ans = (x[n - 1] + x[n - 2] - x[0] - x[1]) / 2.0;
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(10);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}