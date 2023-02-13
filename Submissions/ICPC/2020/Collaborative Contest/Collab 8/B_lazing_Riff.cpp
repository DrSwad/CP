#include <bits/stdc++.h>
using namespace std;

int main() {
  string s;
  cin >> s;

  char ch = 0;
  for (char c : s) {
    if (!ch) ch = c;
    else if (c != ch) {
      puts("2");
      return 0;
    }
  }

  puts("-1");

  return 0;
}