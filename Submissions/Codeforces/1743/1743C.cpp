#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  string s;
  cin >> s;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  long long ans = 0, sum = 0;
  for (int l = 0, mn; l < n; ) {
    if (s[l] == '1') {
      ans += a[l];
      l++;
      continue;
    }
    int r = l + 1;
    sum = mn = a[l];
    while (r < n and s[r] == '1') mn = min(mn, a[r]), sum += a[r], r++;
    ans += sum - mn;
    l = r;
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}