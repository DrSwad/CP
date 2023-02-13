#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  string s;
  cin >> s;

  int en;
  if (n >= 2 and s[0] == s[1]) en = 1;
  else {
    for (en = 1; en < n; en++) {
      if (s[en] > s[en - 1]) break;
    }
  }

  string ans = s.substr(0, en);
  cout << ans + string(ans.rbegin(), ans.rend()) << "\n";
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