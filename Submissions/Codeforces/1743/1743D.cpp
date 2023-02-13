#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  string s;
  cin >> s;

  function<string(int, int)> get_or = [&](int l, int r) {
    string ret;
    int l1 = 0, r1 = n, l2 = l, r2 = r;
    int len = n;
    int at1 = r1 - len, at2 = r2 - len;
    while (at1 < r1 and at2 < r2) {
      char c1 = at1 < 0 ? '0' : s[at1];
      char c2 = at2 < 0 ? '0' : s[at2];
      ret.push_back(c1 | c2);
      at1++, at2++;
    }
    return ret;
  };

  {
    int st;
    for (st = 0; st < n; st++) {
      if (s[st] == '1') break;
    }
    if (st == n) {
      cout << "0\n";
      return;
    }
    s = s.substr(st);
  }

  n = s.length();
  int min_len = n;
  for (int i = 0; i < n and s[i] == '1'; i++) min_len--;

  if (min_len == 0) {
    cout << s << "\n";
    return;
  }

  string ans;
  for (int l = 0; l < n and n - l >= min_len; l++) {
    int len = 0;
    string s2 = s.substr(l, min_len - 1);
    for (int r = l + min_len; r <= n; r++) {
      s2.push_back(s[r - 1]);
      ans = max(ans, get_or(l, r));
    }
  }

  cout << ans << "\n";
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