#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, k;
  scanf("%d %d", &n, &k);

  vector<int> a(n);
  for (int &i: a) scanf("%d", &i);

  int st = max(0, n - 2 * k), en = n - 1;
  long long ans = LLONG_MIN;
  for (int i = st; i < en; i++) {
    for (int j = i + 1; j <= en; j++) {
      ans = max(ans, (long long)(i + 1) * (j + 1) - k * (a[i] | a[j]));
    }
  }

  printf("%lld\n", ans);
}

int main() {
  int t;
  cin >> t;

  while (t--) {
    test_case();
  }

  return 0;
}