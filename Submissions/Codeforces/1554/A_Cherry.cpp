#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    scanf("%d", &n);

    vector<int> a(n);
    for (int &i : a) scanf("%d", &i);

    long long ans = 0;
    for (int i = 0; i < n - 1; i++) {
      int mn = min(a[i], a[i + 1]);
      int mx = max(a[i], a[i + 1]);
      ans = max(ans, mn * 1ll * mx);
    }

    printf("%lld\n", ans);
  }

  return 0;
}