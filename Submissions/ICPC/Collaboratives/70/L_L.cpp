#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string s;
  int carry;

  while (cin >> s >> carry) {
    int sz = s.length();
    string ans;
    for (int i = sz - 1; i >= 0 or carry; i--) {
      int type, val;
      int j = max(i, 0);
      if ('0' <= s[j] and s[j] <= '9') type = 0, val = i >= 0 ? s[i] - '0' : 0;
      else if ('a' <= s[j] and s[j] <= 'z') type = 1, val = i >= 0 ? s[i] - 'a' : -1;
      else if ('A' <= s[j] and s[j] <= 'Z') type = 2, val = i >= 0 ? s[i] - 'A' : -1;
      else assert(false);

      // debug(i, type, val, carry);

      val += carry;
      carry = 0;

      if (type == 0) ans += '0' + (val % 10), carry = val / 10;
      else if (type == 1) ans += 'a' + (val % 26), carry = val / 26;
      else if (type == 2) ans += 'A' + (val % 26), carry = val / 26;
      else assert(false);

      // debug(ans);
    }
    reverse(ans.begin(), ans.end());
    cout << ans << "\n";
  }

  return 0;
}