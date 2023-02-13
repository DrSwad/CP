#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char*argv[]) {
  registerGen(argc, argv, 1);

  const int N = 1e5, A = 1e9;
  int n = rnd.next(N) + 1;
  int k = rnd.next(n) + 1;

  puts("1");
  printf("%d %d\n", n, k);
  for (int i = 0; i < n; i++) {
    printf("%d ", rnd.next(A));
  }
  puts("");

  return 0;
}