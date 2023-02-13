#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, m;
  scanf("%d %d", &n, &m);

  vector<int> a(n), b(m);
  for (int &i : a) scanf("%d", &i);
  for (int &i : b) scanf("%d", &i);

  sort(b.begin(), b.end());

  int L, R;
  scanf("%d %d", &L, &R);

  long long ans = 0;

  for (int i = 0; i < n; i++) {
    if (a[i] == 0) {
      if (L <= 0 and 0 <= R) ans += m;
      continue;
    }

    int l = L, r = R;
    if (a[i] < 0) l = -R, r = -L, a[i] = -a[i];

    l = l < 0 ? -(-l / a[i]) : (l + a[i] - 1) / a[i];
    r = r < 0 ? -((-r + a[i] - 1) / a[i]) : r / a[i];

    int add = upper_bound(b.begin(), b.end(), r) - lower_bound(b.begin(), b.end(), l);
    ans += add;
  }

  printf("%lld\n", ans);

  return 0;
}