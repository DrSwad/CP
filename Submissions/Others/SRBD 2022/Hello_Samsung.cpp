#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string s;
  cin >> s;

  string t = "Samsung";

  int i = 0;
  for (char c : s) {
    if (i < t.length() and c == t[i]) i++;
  }

  if (i == t.length()) cout << "SRBD\n";
  else cout << "GHOST\n";

  return 0;
}