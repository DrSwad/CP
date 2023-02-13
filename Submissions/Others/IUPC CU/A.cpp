#include <bits/stdc++.h>
using namespace std;

int main() {
  string s;
  cin >> s;

  map<char, int> mp;
  int mx = 0;
  for (char c : s) {
    mp[c]++;
    mx = max(mx, mp[c]);
  }

  puts(mx == 1 ? "YES" : "NO");

  return 0;
}