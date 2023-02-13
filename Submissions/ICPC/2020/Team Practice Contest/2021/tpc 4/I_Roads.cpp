#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, a;
    scanf("%d %d", &n, &a);

    if (a > n) {
      puts("-1");
      continue;
    }

    if (a == 1) {
      if (n == 1) puts("0");
      else if (n == 2) {
        puts("1");
        puts("1 2");
      }
      else puts("-1");
    }
    else if (a == 2) {
      if (n == 2) puts("-1");
      else {
        printf("%d\n", n - 1);
        for (int i = 1; i < n; i++) {
          printf("%d %d\n", 1, i + 1);
        }
      }
    }
    else if (a == 3) {
      if (n > 4) {
        printf("%d\n", n - 1);
        int n2 = (n - 1) / 2;
        for (int i = 1; i < n2; i++) {
          printf("%d %d\n", i, n2);
          printf("%d %d\n", n - (i - 1), n - (n2 - 1));
        }
        printf("%d %d\n", n2, n2 + 1);
        printf("%d %d\n", n2 + 1, n2 + 2);
        if (n % 2 == 0) printf("%d %d\n", n2 + 2, n2 + 3);
      }
      else puts("-1"); // Need to verify
    }
    else if (a < n) {
      printf("%d\n", n - 1);
      for (int i = 2; i <= 1 + (a - 2); i++) {
        printf("%d %d\n", i - 1, i);
      }
      for (int i = a; i <= n; i++) {
        printf("%d %d\n", 1, i);
      }
    }
    else if (a <= 6) puts("-1"); // Need to verify
    else {
      printf("%d\n", n - 1);
      puts("1 2");
      puts("1 3");
      puts("3 4");
      puts("1 5");
      for (int i = 5; i < n; i++) {
        printf("%d %d\n", i, i + 1);
      }
    }
  }

  return 0;
}