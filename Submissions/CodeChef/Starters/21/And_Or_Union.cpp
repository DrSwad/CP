#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<int> f(30, 0);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 30; j++) {
      f[j] += (a[i] >> j & 1);
    }
  }

  int ans = 0;
  for (int i = 0; i < 30; i++) {
    ans += (1 << i) * (f[i] >= 2);
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