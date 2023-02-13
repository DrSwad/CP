#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<long long> a(n);
  for (long long &i : a) cin >> i;

  sort(a.begin(), a.end());

  long long ans = LLONG_MIN;
  ans = max(ans, a[n - 1] - a[0]);

  for (int i = 0; i < n - 2; i++) {
    ans = max(ans, abs(a[i + 1] - a[i]) + abs(a[n - 1] - a[i]));
  }

  for (int i = n - 1; i >= 2; i--) {
    ans = max(ans, abs(a[i - 1] - a[i]) + abs(a[0] - a[i]));
  }

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