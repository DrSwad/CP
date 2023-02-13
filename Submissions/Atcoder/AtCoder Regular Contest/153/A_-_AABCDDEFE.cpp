#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;
  n += (int)1e5 - 1;

  string s = to_string(n);
  while (s.length() < 6) s.insert(s.begin(), '0');
  s.insert(s.begin() + 0, s[0]);
  s.insert(s.begin() + 4, s[4]);
  s.insert(s.end(), s[6]);

  cout << s << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  // cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}