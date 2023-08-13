#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<vector<int>> a(n);
  vector<int> b(n);
  int mn = INT_MAX;
  for (int i = 0; i < n; i++) {
    int sz;
    cin >> sz;
    a[i].resize(sz);
    for (int &j : a[i]) cin >> j;
    sort(a[i].begin(), a[i].end());
    b[i] = a[i][1];
    mn = min(mn, a[i][0]);
  }

  sort(b.begin(), b.end());
  long long ans = mn;
  for (int i = 1; i < n; i++) {
    ans += b[i];
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}