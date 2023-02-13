#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, k;
  scanf("%d %d", &n, &k);

  vector<int> a(n);
  for (int &i : a) scanf("%d", &i);

  int mx = *max_element(a.begin(), a.end());
  long long ans = 0;

  for (int i = k - 1; i < n; i++) {
    if (a[i] == mx) {
      ans += n - i;
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