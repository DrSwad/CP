#include <bits/stdc++.h>
using namespace std;

bool is_palindrome(string s) {
  string t = s;
  reverse(s.begin(), s.end());
  return s == t;
}

void test_case() {
  string x, y;
  cin >> x >> y;

  int nx = x.length();
  int ny = y.length();

  int ans = 0;
  for (int lx = 0; lx < nx; lx++) {
    for (int rx = lx + 1; rx <= nx; rx++) {
      string sx = x.substr(lx, rx - lx);

      for (int ly = 0; ly < ny; ly++) {
        for (int ry = ly + 1; ry <= ny; ry++) {
          string sy = y.substr(ly, ry - ly);

          ans += is_palindrome(sx + sy);
        }
      }
    }
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}