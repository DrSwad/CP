#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  scanf("%d", &n);

  vector<int> a(n);
  long long ans = 0;
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
    if (i) ans += max(0, a[i - 1] - a[i]);
  }

  cout << ans << endl;

  return 0;
}