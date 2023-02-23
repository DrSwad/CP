#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char*argv[]) {
  registerGen(argc, argv, 1);

  const int N = 6, A = 10;

  puts("1");
  int n = rnd.next(N) + 1;
  printf("%d\n", n);

  while (n--) {
    cout << rnd.next(A) + 1 << " ";
  }
  puts("");

  return 0;
}