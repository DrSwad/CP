#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n), b(n);
  for (int &i : a) cin >> i, i--;
  for (int &i : b) cin >> i, i--;

  vector<int> ma(n), mb(n);
  for (int i = 0; i < n; i++) {
    ma[a[i] / 2] = i;
    mb[b[i] / 2] = i;
  }

  int mn = n;
  int ans = n;

  for (int i = 0; i < n; i++) {
    mn = min(mn, ma[i]);
    ans = min(ans, mb[i] + mn);
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}