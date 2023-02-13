#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char*argv[]) {
  registerGen(argc, argv, 1);

  const int N = 10;

  int n = rnd.next(N) + 1;
  int m = rnd.next(N) + 1;
  printf("%d %d\n", n, m);

  while (n--) {
    cout << rnd.next("[RGB*]{%d}", m) << endl;
  }

  return 0;
}