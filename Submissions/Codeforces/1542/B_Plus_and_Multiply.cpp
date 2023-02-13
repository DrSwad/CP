#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;

  while (t--) {
    long long n, a, b;
    scanf("%lld %lld %lld", &n, &a, &b);

    bool flag = false;
    long long x = 1;
    do {
      flag = flag or (x <= n and (n - x) % b == 0);
      x *= a;
    } while (a > 1 and x <= n);

    puts(flag ? "Yes" : "No");
  }

  return 0;
}