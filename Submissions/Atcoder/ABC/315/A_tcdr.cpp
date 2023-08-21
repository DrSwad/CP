#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string s;
  cin >> s;

  for (char c : s) {
    if (c == 'a') continue;
    if (c == 'e') continue;
    if (c == 'i') continue;
    if (c == 'o') continue;
    if (c == 'u') continue;
    cout << c;
  }
  cout << "\n";

  return 0;
}