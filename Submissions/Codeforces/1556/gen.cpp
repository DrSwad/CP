#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  const int N = 100, A = 5;

  int n = rnd.next(N - 1) + 2;
  int q = rnd.next(N) + 1;
  printf("%d %d\n", n, q);

  for (int i = 1; i <= n; i++) {
    if (i > 1) printf(" ");
    printf("%d", rnd.next(2 * A + 1) - A);
  }
  puts("");

  for (int i = 1; i <= n; i++) {
    if (i > 1) printf(" ");
    printf("%d", rnd.next(A));
  }
  puts("");

  while (q--) {
    int l = rnd.next(n - 1) + 1;
    int r = rnd.next(n - l) + l + 1;
    printf("%d %d\n", l, r);
  }

  return 0;
}