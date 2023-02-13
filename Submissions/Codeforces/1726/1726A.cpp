#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  int ans = a[n - 1] - a[0];
  for (int i = 0; i < n; i++) {
    ans = max(ans, a[(i - 1 + n) % n] - a[i]);
  }

  if (n > 1) {
    ans = max(ans, a[n - 1] - *min_element(a.begin(), prev(a.end())));
    ans = max(ans, *max_element(a.begin() + 1, a.end()) - a[0]);
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