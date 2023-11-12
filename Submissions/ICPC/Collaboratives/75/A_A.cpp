#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string s, t;
  cin >> s >> t;

  int len = s.length();
  while (len--) {
    rotate(s.begin(), s.begin() + 1, s.end());
    if (s == t) {
      cout << "Yes\n";
      return 0;
    }
  }

  cout << "No\n";

  return 0;
}