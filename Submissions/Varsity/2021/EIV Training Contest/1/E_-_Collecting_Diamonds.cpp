#include <bits/stdc++.h>
using namespace std;

int brute(string s) {
  // DB();
  // debug(s);
  int n = s.length();
  if (n <= 2) return 0;

  int ret = 0;
  for (int i = 0; i < n - 2; i++) {
    if (s[i] == 'A' and s[i + 1] == 'B' and s[i + 2] == 'C') {
      string ns = s;
      if (i % 2 == 0) {
        ns.erase(i + 2, 1);
        ns.erase(i, 1);
      }
      else {
        ns.erase(i + 1, 1);
      }
      ret = max(ret, 1 + brute(ns));
    }
  }

  // debug(ret);
  return ret;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  // while (true) {
  string s;
  cin >> s;

  vector<pair<int, int>> v;
  int n = s.length();
  for (int i = 0; i < n; i++) {
    if (s[i] == 'B') {
      int len = 0;
      for (int p1 = i - 1, p2 = i + 1; p1 >= 0 and p2 < n; p1--, p2++) {
        if (s[p1] == 'A' and s[p2] == 'C') len++;
        else break;
      }
      if (len) v.push_back({(i + 1) & 1, len});
    }
  }

  int ans = 0;
  int carry = 0;

  for (auto [p, len] : v) {
    if (carry == 0) {
      if (p) ans++, carry++;
      else {
        if (len == 1) ans++;
        else ans += 2, carry++;
      }
    }
    else {
      int ncarry = carry;
      if (p == 0) ncarry++;
      ans += min(ncarry, len - 1);
      ans++;
      carry++;
    }
  }

  // assert(ans == brute(s));
  cout << ans << "\n";
  // }

  return 0;
}