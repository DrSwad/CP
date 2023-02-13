#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;

  while (t--) {
    int l, r;
    scanf("%d %d", &l, &r);

    int m = (r + 1) / 2;
    int ans = INT_MIN;
    if (m >= l) ans = max(ans, m - 1);
    ans = max(ans, r - max(m + 1, l));
    printf("%d\n", ans);
  }

  return 0;
}