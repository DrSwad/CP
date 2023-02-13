#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  const int N = 8, A = 16;

  int n = rnd.next(N) + 1;
  printf("%d\n", n);

  for (int i = 0; i < n; i++) {
    if (i) printf(" ");
    printf("%d", rnd.next(A));
  }
  puts("");

  for (int i = 0; i < n; i++) {
    if (i) printf(" ");
    printf("%d", rnd.next(A));
  }
  puts("");

  return 0;
}