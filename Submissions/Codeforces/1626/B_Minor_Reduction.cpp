#include <bits/stdc++.h>
using namespace std;

void test_case() {
  string s;
  cin >> s;

  int n = s.length();

  int at = -1;
  for (int i = 0; i < n - 1; i++) {
    if (s[i] - '0' + s[i + 1] - '0' >= 10) at = i;
  }

  if (at == -1) at = 0;

  string ans;
  for (int i = 0; i < at; i++) ans += s[i];
  ans += to_string(s[at] - '0' + s[at + 1] - '0');
  for (int i = at + 2; i < n; i++) ans += s[i];

  cout << ans << "\n";
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