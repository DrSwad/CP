#include <bits/stdc++.h>
using namespace std;

void test_case() {
  string s;
  cin >> s;

  int n = s.length();

  if (n == 1) cout << "NO\n";
  else {
    if (n == 2 and s == "()") cout << "NO\n";
    else {
      cout << "YES\n";
      string ans = string(n, '(') + string(n, ')');
      if (ans.find(s) == string::npos) cout << ans << "\n";
      else {
        string pattern = "()";
        ans = "";
        for (int i = 0; i < n; i++) ans += pattern;
        cout << ans << "\n";
      }
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