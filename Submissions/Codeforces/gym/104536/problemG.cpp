#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;
  a.insert(a.begin(), -1);

  long long ans = 0;
  int zero = 0;

  for (int i = 1; i <= n; i++) {
    if (a[i] - i == 0) zero++;
    else {
      int mul = abs(a[i] - i);
      for (int div = 1; div * div <= mul; div++) {
        if (mul % div == 0) {
          for (int it = 0; it < 2; it++) {
            if (it == 1 and div * div == mul) break;
            int cur_div = it == 0 ? div : mul / div;
            int j = cur_div - i;
            if (j <= 0 or j > n or i == j) continue;
            if (a[j] - j == 0) ans++;
            else if (j > i and gcd(a[i] + j, a[j] + i) == i + j) ans++;
          }
        }
      }
    }
  }

  ans += 1ll * zero * (zero - 1) / 2;

  cout << ans << "\n";

  return 0;
}