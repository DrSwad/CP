#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;

  vector<int> a(n), b(n);
  for (int &i : a) scanf("%d", &i);
  for (int &i : b) scanf("%d", &i);

  vector<int> c(n);
  for (int i = 0; i < n; i++) {
    c[i] = -(a[i] - b[i]);
  }
  sort(c.begin(), c.end());

  long long ans = 0;
  for (int i = 0; i < n; i++) {
    ans += lower_bound(c.begin(), c.end(), a[i] - b[i]) - c.begin();
    ans -= (a[i] - b[i]) > -(a[i] - b[i]);
  }

  printf("%lld\n", ans / 2);

  return 0;
}