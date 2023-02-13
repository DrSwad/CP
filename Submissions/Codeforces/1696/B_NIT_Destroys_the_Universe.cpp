#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  if (count(a.begin(), a.end(), 0) == n) {
    cout << "0\n";
    return;
  }

  int cnt = 0;
  int l, r;
  for (l = 0; l < n; l++) {
    if (a[l] != 0) break;
    cnt++;
  }
  for (r = n - 1; r >= l; r--) {
    if (a[r] != 0) break;
    cnt++;
  }
  if (count(a.begin(), a.end(), 0) == cnt) {
    cout << "1\n";
    return;
  }

  cout << "2\n";
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