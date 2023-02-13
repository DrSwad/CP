#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> ans(n);
  for (int i = 0; i < n / 2; i++) {
    ans[i] = n - 2 * i - 1;
    ans[n - 1 - i] = n - 2 * i - 2;
  }
  if (n % 2 == 1) ans[n / 2] = 0;

  for (int i = 0; i < n; i++) {
    if (i) cout << " ";
    cout << ans[i] + 1;
  }
  cout << "\n";
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