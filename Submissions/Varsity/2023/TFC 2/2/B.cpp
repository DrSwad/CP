#include <bits/stdc++.h>
using namespace std;

typedef unsigned int uint;
typedef unsigned long long ull;

bitset<1ll << 31> bs;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int q;
  uint s, a, b;
  cin >> q >> s >> a >> b;

  ull ans = 0;

  while (q--) {
    uint ss = s / 2;
    if (s & 1) {
      if (!bs[ss]) {
        ans += ss;
        bs[ss] = true;
      }
    }
    else {
      if (bs[ss]) {
        ans -= ss;
        bs[ss] = false;
      }
    }

    s = a * s + b;
  }

  cout << ans << "\n";

  return 0;
}