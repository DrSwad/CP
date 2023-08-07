#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  int mx = 0;
  for (int i = 0; i < n; i++) {
    bool bad = false;
    for (int j = i + 1; j < n; j++) {
      if (a[j] < a[i]) {
        bad = true;
        break;
      }
    }
    if (bad) mx = max(mx, a[i]);
  }

  cout << mx << "\n";
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