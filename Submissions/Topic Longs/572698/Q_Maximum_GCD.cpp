#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  int ans = 1;
  auto consider =
    [&](int g) {
      if (g == 0) return;
      for (int i = 0; i < n; i++) {
        if (a[i] % g != 0 and 2 * g >= a[i]) return;
      }
      ans = max(ans, g);
    };

  int mn_a = *min_element(a.begin(), a.end());
  consider((mn_a + 1) / 2 - 1);
  consider(mn_a / 2);
  consider(mn_a);

  cout << ans << "\n";

  return 0;
}