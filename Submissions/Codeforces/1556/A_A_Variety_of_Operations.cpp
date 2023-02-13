#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
  int t;
  cin >> t;

  while (t--) {
    ll c, d;
    scanf("%lld %lld", &c, &d);

    if (c == 0 and d == 0) puts("0");
    else if (c == d or c == -d) puts("1");
    else if (c % 2 != d % 2) puts("-1");
    else puts("2");
  }

  return 0;
}