#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, m;
  cin >> n >> m;

  int ans = INT_MAX;

  vector<int> a(m);
  for (int &i : a) cin >> i;

  sort(a.begin(), a.end());

  for (int i = 0; i <= m - n; i++) {
    ans = min(ans, a[i + n - 1] - a[i]);
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  // cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}