#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    printf("Case #%d:", cs);

    int x, y;
    string s;
    cin >> x >> y >> s;

    int ans = 1000;
    int n = s.length();
    for (int mask = 0; mask < 1 << n; mask++) {
      bool valid = true;
      for (int i = 0; i < n; i++) {
        if (s[i] != '?' and (s[i] == 'J') != (mask >> i & 1)) {
          valid = false;
        }
      }

      if (valid) {
        int curr = 0;
        for (int i = 0; i < n - 1; i++) {
          if ((mask >> i & 1) != (mask >> (i + 1) & 1)) {
            curr += (mask >> i & 1) ? y : x;
          }
        }
        ans = min(ans, curr);
      }
    }

    printf(" %d\n", ans);
  }

  return 0;
}