#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;

  while (t--) {
    string s;
    cin >> s;
    reverse(s.begin(), s.end());

    int rem = 0;
    for (int i = 0, r = 1; i < s.size(); i++) {
      (rem += r * (s[i] - '0')) %= 3;
      (r *= 2) %= 3;
    }

    if (rem) puts("Malvika");
    else puts("Animesh");
  }

  return 0;
}