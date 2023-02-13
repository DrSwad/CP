#include <bits/stdc++.h>
using namespace std;

void test_case() {
  vector<string> s(3);
  for (string &ss : s) cin >> ss;

  string t;
  cin >> t;

  string ans;
  for (char c : t) {
    ans += s[c - '1'];
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  // cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}