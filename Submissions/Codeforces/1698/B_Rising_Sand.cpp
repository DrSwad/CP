#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, k;
  cin >> n >> k;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  if (k > 1) {
    int ans = 0;
    for (int i = 1; i < n - 1; i++) {
      ans += a[i] > a[i - 1] + a[i + 1];
    }
    cout << ans << "\n";
  }
  else {
    int ans = 0;
    for (int i = 1; i < n - 1; i += 2) {
      ans++;
    }
    cout << ans << "\n";
  }
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