#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, a, b, c, x;
  cin >> n >> a >> b >> c >> x;

  int ans = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      for (int k = 1; k <= n; k++) {
        if (a * i + b * j + c * k == x) {
          ans++;
        }
      }
    }
  }

  cout << ans << "\n";

  return 0;
}