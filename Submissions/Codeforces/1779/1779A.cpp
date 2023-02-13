#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  string s;
  cin >> s;

  if (count(s.begin(), s.end(), 'R') == n) cout << "-1\n";
  else if (count(s.begin(), s.end(), 'L') == n) cout << "-1\n";
  else {
    int rightmost_l = 1;
    for (int i = 1; i <= n; i++) {
      if (s[i - 1] == 'L') rightmost_l = i;
    }
    if (rightmost_l == n) cout << "0\n";
    else cout << rightmost_l << "\n";
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