#include <bits/stdc++.h>

using namespace std;

int s, c, d, p;

int call(int a, int d = 0) {
  if (d >= 20) return 123456789;
  // cout << a << '\n';
  if (a == c) return 0;
  return 1 + min(call((a + a) % p, d + 1), call((a + a - s + p) % p, d + 1));
}

int main() {
  int a, b, q;
  cin >> p >> q;
  while (q--) {
    cin >> a >> b >> c >> d;
    if ((a + b) % p != (c + d) % p) {
      cout << "-1\n";
      continue;
    } else {
      s = a + b;
      int ans = call(a);
      // if(ans >= 10) cout << "-1\n";
      cout << ans << '\n';
    }
  }
}