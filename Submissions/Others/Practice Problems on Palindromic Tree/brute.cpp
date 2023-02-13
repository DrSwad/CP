#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    printf("Case #%d: ", cs);

    string a, b;
    cin >> a >> b;
    int ans = 0;
    for (int i0 = 0; i0 < a.length(); i0++) {
      for (int j0 = 1; i0 + j0 <= a.length(); j0++) {
        string _a = a.substr(i0, j0);
        reverse(_a.begin(), _a.end());
        if (a.substr(i0, j0) != _a) continue;
        for (int i1 = 0; i1 < b.length(); i1++) {
          for (int j1 = 1; i1 + j1 <= b.length(); j1++) {
            ans += a.substr(i0, j0) == b.substr(i1, j1);
          }
        }
      }
    }
    printf("%d\n", ans);
  }

  return 0;
}