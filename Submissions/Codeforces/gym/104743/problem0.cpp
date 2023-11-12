#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, k;
  cin >> n >> k;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  if (count(a.begin(), a.end(), 0) == n) {
    cout << "0\n";
    return;
  }

  for (int bit = 0; bit < 30 and (1 << bit) <= k; bit++) {
    bool found = false;
    for (int i = 0; i < n; i++) {
      if (a[i] >> bit & 1) {
        found = true;
        break;
      }
    }
    if (!found) {
      cout << "1\n";
      return;
    }
  }

  if (k >= 2) cout << "2\n";
  else cout << "-1\n";
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