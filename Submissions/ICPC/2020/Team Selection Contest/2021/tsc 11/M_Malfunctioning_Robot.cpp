#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;

  while (t--) {
    long long x1, y1, x2, y2;
    scanf("%lld %lld %lld %lld", &x1, &y1, &x2, &y2);

    long long dx = abs(x1 - x2);
    long long dy = abs(y1 - y2);
    long long diff = abs(dx - dy);

    long long ans = dx + dy + diff;
    if (diff & 1) ans--;

    printf("%lld\n", ans);
  }

  return 0;
}
