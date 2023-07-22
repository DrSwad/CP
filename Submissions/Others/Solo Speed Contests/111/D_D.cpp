#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int s, x1, x2;
  cin >> s >> x1 >> x2;

  int t1, t2;
  cin >> t1 >> t2;

  int p, d;
  cin >> p >> d;

  int ans = abs(x1 - x2) * t2;

  int t = 0;
  bool found = false;
  while (p != x2 or !found) {
    if (p == x1) found = true;
    p += d;
    if (p == 0 or p == s) d *= -1;
    t += t1;
  }

  ans = min(ans, t);

  cout << ans << "\n";

  return 0;
}