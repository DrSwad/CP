#include <bits/stdc++.h>
using namespace std;

void test_case(string s) {
  int n = s.length();
  int ans = 0;
  for (int l = n / 2 - 1, r = n - 1 - l, carry = 0; r < n; r++, l--) {
    int cur = (s[l] - s[r] - carry) % 26;
    if (cur < 0) cur += 26;
    ans += cur;
    carry += cur;
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string s;
  while (cin >> s) {
    test_case(s);
  }

  return 0;
}
