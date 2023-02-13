#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  char c;
  cin >> c;

  string s;
  cin >> s;

  int at = n - 1;
  while (~at and s[at] != c) at--;

  if (s == string(n, c)) cout << "0\n\n";
  else if (2 * (at + 1) > n) cout << "1\n" << (at + 1) << "\n";
  else cout << "2\n" << n << " " << (n - 1) << "\n";
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