#include <bits/stdc++.h>
using namespace std;

const int MX = 1e8;

void test_case() {
  int a, b, c;
  cin >> a >> b >> c;

  long long x, y, z;
  y = b;
  z = c;
  x = y * MX + a;

  cout << x << " " << y << " " << z << "\n";
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