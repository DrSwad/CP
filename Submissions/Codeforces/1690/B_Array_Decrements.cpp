#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n), b(n);
  for (int &i : a) cin >> i;
  for (int &i : b) cin >> i;

  int lb = -1, fixed = -1;
  for (int i = 0; i < n; i++) {
    if (a[i] < b[i]) {
      cout << "NO\n";
      return;
    }

    if (b[i] == 0) {
      lb = max(lb, a[i] - b[i]);
      if (fixed != -1 and fixed < lb) {
        cout << "NO\n";
        return;
      }
    }
    else {
      if (fixed != -1 and fixed != a[i] - b[i]) {
        cout << "NO\n";
        return;
      }
      fixed = a[i] - b[i];
      if (fixed < lb) {
        cout << "NO\n";
        return;
      }
    }
  }

  cout << "YES\n";
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