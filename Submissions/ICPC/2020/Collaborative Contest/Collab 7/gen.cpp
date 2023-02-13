#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char*argv[]) {
  registerGen(argc, argv, 1);

  const int N = 100;
  int t = N * N;

  printf("%d\n", t);
  for (int n = 1; n <= N; n++) {
    for (int m = 1; m <= N; m++) {
      printf("%d %d\n", n, m);
    }
  }
  // while (t--) {
  //   // int n = rnd.next(N) + 1, m = rnd.next(N + 1);
  //   int m = rnd.next(N + 1);
  //   int n = m - 1;
  //   if (n > m) swap(n, m);
  //   printf("%d %d\n", n, m);
  // }

  return 0;
}