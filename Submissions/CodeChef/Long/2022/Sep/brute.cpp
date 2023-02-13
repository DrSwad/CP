#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  string s;
  cin >> n >> s;

  set<string> palindromes;
  string t;

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j <= n; j++) {
      string ss = s.substr(i, j - i);
      string rs = ss;
      reverse(rs.begin(), rs.end());
      if (ss == rs) palindromes.insert(ss);
    }
  }

  for (const string &s : palindromes) t += s;

  int q;
  cin >> q;

  while (q--) {
    int l, r;
    cin >> l >> r;

    if (r > t.length()) {
      cout << "-1\n";
      continue;
    }

    for (int i = l; i <= r; i++) {
      cout << t[i - 1];
    }
    cout << "\n";
  }

  return 0;
}