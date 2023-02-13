#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;

  while (t--) {
    string s;
    cin >> s;
    int n = s.length();

    puts((n & 1) ^ (s[0] == s.back()) ? "Chikapu" : "Bash");
  }

  return 0;
}
