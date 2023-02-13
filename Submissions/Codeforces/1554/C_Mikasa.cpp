#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 40;

int main() {
  int t;
  cin >> t;

  while (t--) {
    ll n, m;
    scanf("%lld %lld", &n, &m);
    m = max(0ll, m - n + 1);

    ll full = (1ll << N) - 1;
    ll nn = full ^ n;

    ll add = 0, ans = LLONG_MAX;
    for (int i = N - 1; ~i; i--) {
      if ((nn >> i & 1) == 0) continue;

      ll curr = add + (1ll << i);
      if (curr >= m) ans = min(ans, curr);
      if (m >> i & 1) add = curr;
    }
    if (m == 0) ans = 0;

    printf("%lld\n", ans);
  }

  return 0;
}