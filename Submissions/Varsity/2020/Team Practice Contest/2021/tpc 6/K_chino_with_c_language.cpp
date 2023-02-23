#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  string s;
  int p1, p2, l;

  cin >> n >> s >> p1 >> p2 >> l;
  p1--, p2--;

  string ans1 = s, ans2 = s;
  for (int i = 0; i < l; i++) {
    ans1[p2 + i] = ans1[p1 + i];
    ans2[p2 + i] = s[p1 + i];
  }

  cout << ans1 << "\n" << ans2 << "\n";

  return 0;
}