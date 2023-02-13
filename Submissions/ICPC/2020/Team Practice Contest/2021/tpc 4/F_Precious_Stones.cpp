#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int main() {
  int t;
  cin >> t;

  char s[N];
  for (int cs = 1; cs <= t; cs++) {
    scanf("%s", s);
    int n = strlen(s);

    vector<int> segs{1};
    for (int i = 1; i < n; i++) {
      if (s[i] == s[i - 1]) segs.back()++;
      else segs.push_back(1);
    }
    if (segs.size() > 1 and s[n - 1] == s[0]) {
      segs[0] += segs.back();
      segs.pop_back();
    }

    int ans;
    if (segs.size() == 1) {
      if (n == 1) ans = 1;
      else ans = n / 2;
    }
    else {
      int max1 = 0, max2 = 0;
      for (int seg : segs) {
        if (!max1 or seg >= max1) max2 = max1, max1 = seg;
        else if (!max2 or seg >= max2) max2 = seg;
      }

      if (max1 == 1) ans = min(3, n);
      else if (max1 == 2) {
        if (max2 == 1) ans = 2;
        else if (n == 4) ans = 3;
        else ans = 2;
      }
      else ans = max(max1 / 2, max2);
    }

    printf("Case %d: %d\n", cs, ans);
  }

  return 0;
}