#include <bits/stdc++.h>
using namespace std;

void test_case() {
  string s;
  cin >> s;

  int n = s.length();

  if (n == 1) cout << s << "\n";
  else if (n == 2) cout << s[1] << "\n";
  else cout << *min_element(s.begin(), s.end()) << "\n";
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