#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    printf("Case #%d: ", cs);

    int n;
    scanf("%d", &n);

    vector<int> a(n);
    for (int i = 0; i < n; i++) { scanf("%d", &a[i]); }

    long long ans = 0;
    for (int i = 0; i < n - 1; i++) {
      int minAt = min_element(a.begin() + i, a.end()) - a.begin();
      ans += minAt - i + 1;
      reverse(a.begin() + i, a.begin() + minAt + 1);
    }

    printf("%lld\n", ans);
  }

  return 0;
}