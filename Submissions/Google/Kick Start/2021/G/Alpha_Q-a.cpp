#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

char s[N];
int t, cs, n;
long long d, c, m;

int main() {
  cin >> t;
  while (t--) {
    scanf("%d %lld %lld %lld %s", &n, &d, &c, &m, s + 1);
    int en = 0;
    for (int i = 1; i <= n; ++i) {
      if (s[i] == 'D') {
        if (d) --d, c += m;
        else break;
      } else {
        if (c) --c;
        else break;
      }
      en = i;
    }
    bool ok = 1;
    for (int i = en + 1; i <= n; ++i) {
      if (s[i] == 'D') {
        ok = 0;
        break;
      }
    }
    printf("Case #%d: ", ++cs);
    puts(ok ? "YES" : "NO");
  }
  return 0;
}

