#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);

  const int N = 10;
  const int T = 100;

  int n = rnd.next(N) + 1;
  printf("%d\n", n);
  for (int i = 0; i < n; i++) printf("%d ", rnd.next(T) + 1);
  puts("");
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < n; j++) {
      printf("%d ", rnd.next(T) + 1);
    }
    puts("");
  }

  return 0;
}