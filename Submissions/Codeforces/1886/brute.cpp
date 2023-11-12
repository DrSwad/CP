#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  for (int x = 1; x < n; x++) {
    for (int y = 1; y < n; y++) {
      for (int z = 1; z < n; z++) {
        if (x + y + z == n and
            x != y and y != z and x != z and
            x % 3 != 0 and y % 3 != 0 and z % 3 != 0
        ) {
          cout << "YES\n";
          return;
        }
      }
    }
  }

  cout << "NO\n";
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