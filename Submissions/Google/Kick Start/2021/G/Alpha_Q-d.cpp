#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll area;
int t, cs, n;

int main() {
  cin >> t;
  while (t--) {
    cin >> n >> area;
    printf("Case #%d: ", ++cs);
    if (area < n - 2) {
      puts("IMPOSSIBLE");
      continue;
    }
    puts("POSSIBLE");
    ll ext = area - (n - 2), half = n >> 1;
    if (n == 3) {
      puts("0 0");
      puts("1 0");
      printf("0 %lld\n", area);
      continue;
    }
    if (n == 4) {
      puts("0 1");
      puts("0 0");
      puts("1 0");
      printf("1 %lld\n", 1 + ext);
      continue;
    }
    if (n & 1) {
      for (int i = 0; i < half; ++i) {
        printf("%d 1\n", i);
        printf("%d 0\n", i + 1);
      }
      printf("%lld 2\n", half - 1 + ext);
      continue;
    }
    puts("0 0");
    puts("0 1");
    printf("1 %lld\n", 2 + ext);
    for (int i = 1; i < half - 1; ++i) {
      printf("%d 1\n", i);
      printf("%d 2\n", i + 1);
    }
    printf("%lld 1\n", half - 1);
  }
  return 0;
}

