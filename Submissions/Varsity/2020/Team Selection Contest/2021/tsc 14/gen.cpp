#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
const int X = 1e9;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  puts("1");
  const int _N = 5;
  const int _X = 5;

  int n = rnd.next(_N) + 1;
  printf("%d\n", n);

  for (int i = 0; i < 2 * n; i++) {
    int x, y;
    x = rnd.next(2 * _X) - _X;
    y = rnd.next(2 * _X) - _X;
    printf("%d %d\n", x, y);
  }

  return 0;
}