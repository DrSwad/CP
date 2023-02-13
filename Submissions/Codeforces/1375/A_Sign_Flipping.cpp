#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  for (int i = 0; i + 2 < n; i += 2) {
    bool flag = false;
    for (int j = 0; j < 2 and !flag; j++) {
      a[i + 1] *= -1;
      for (int k = 0; k < 2 and !flag; k++) {
        a[i + 2] *= -1;
        int d1 = a[i + 1] - a[i], d2 = a[i + 2] - a[i + 1];
        if (d1 > 0 and d2 > 0) continue;
        if (d1 < 0 and d2 < 0) continue;
        flag = true;
      }
    }
  }

  for (int i = 0; i < n; i++) {
    if (i) cout << " ";
    cout << a[i];
  }
  cout << "\n";
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