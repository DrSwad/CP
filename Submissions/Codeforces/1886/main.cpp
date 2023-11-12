#include <bits/stdc++.h>
using namespace std;

void validate(int n, int x, int y, int z) {
  assert(
    x + y + z == n and
    x != y and y != z and x != z and
    x % 3 != 0 and y % 3 != 0 and z % 3 != 0
  );
}

void test_case() {
  int n;
  cin >> n;

  if (n < 6) cout << "NO\n";
  else {
    int x = 1, y = 2, z = n - 3;
    if (z % 3 == 0) {
      z -= 2;
      y += 2;
    }
    if (y >= z) cout << "NO\n";
    else {
      cout << "YES\n";
      validate(n, x, y, z);
    }
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