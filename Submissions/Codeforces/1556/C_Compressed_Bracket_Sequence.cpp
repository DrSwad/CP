#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
  int n;
  scanf("%d",  &n);

  vector<int> c(n);
  for (int &i : c) scanf("%d", &i);

  ll ans = 0;

  for (int i = 0; i < n; i += 2) {
    ll mx = 0, curr = 0;

    for (int j = i + 1; j < n; j++) {
      if (j % 2 == 1) {
        ll min_b = max(max(1ll, -curr + 1), mx - curr);
        ll max_b = min((ll)c[j], (ll)c[i] - curr);
        ans += max(0ll, max_b - min_b + 1);
      }

      if (j % 2 == 1) curr += c[j];
      else curr -= c[j];

      mx = max(mx, curr);
    }
  }

  printf("%lld\n", ans);

  return 0;
}