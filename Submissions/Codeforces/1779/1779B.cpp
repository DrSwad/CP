#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  if (n == 3) cout << "NO\n";
  else if (n % 2 == 0) {
    cout << "YES\n";
    for (int i = 0; i < n; i += 2) {
      if (i) cout << " ";
      cout << "1 -1";
    }
    cout << "\n";
  }
  else {
    cout << "YES\n";
    int a = (n - 1) / 2 - 1;
    for (int i = 0; i + 2 < n; i += 2) {
      if (i) cout << " ";
      cout << a << " " << -(a + 1);
    }
    cout << " " << a << "\n";
  }
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