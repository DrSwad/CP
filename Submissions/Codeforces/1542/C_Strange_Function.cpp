#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
  int t;
  cin >> t;

  while (t--) {
    long long n;
    scanf("%lld", &n);

    long long ans = n;
    long long L = 1, num = 1;
    while (L <= n) {
      ans += n / L;
      L = lcm(L, ++num);
    }

    printf("%lld\n", ans % MOD);
  }

  return 0;
}