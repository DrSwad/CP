#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  scanf("%d", &n);

  map<int, int> mp;
  for (int i = 0; i < n; i++) {
    int w;
    scanf("%d", &w);
    mp[w - i]++;
  }

  int ans = 0;
  for (auto [key, val] : mp) {
    ans = max(ans, val);
  }

  printf("%d\n", ans);
}

int main() {
  int t;
  cin >> t;

  while (t--) {
    test_case();
  }

  return 0;
}