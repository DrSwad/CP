#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, x;
  cin >> n >> x;

  if (x < n) cout << "-1\n";
  else {
    cout << x - (n - 1);
    for (int i = 1; i <= n; i++) {
      if (i != x - (n - 1)) {
        cout << " " << i;
      }
    }
    cout << "\n";
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