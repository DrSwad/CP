#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char*argv[]) {
  registerGen(argc, argv, 1);

  const int N = 10;

  puts("1");

  int n = rnd.next(N) + 1;
  cout << rnd.next("[AR]{%d}", n) << endl;

  return 0;
}