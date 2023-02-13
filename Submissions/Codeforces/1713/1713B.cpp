#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  int l, r;
  for (l = 0; l < n - 1; l++) {
    if (a[l] > a[l + 1]) break;
  }
  for (r = n - 1; r > 0; r--) {
    if (a[r] > a[r - 1]) break;
  }

  cout << (r <= l ? "YES\n" : "NO\n");
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