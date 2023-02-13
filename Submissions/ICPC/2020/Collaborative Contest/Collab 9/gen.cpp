#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  const int N = 20;

  cout << rnd.next(N) + 1 << " " << rnd.next(N) + 1 << endl;

  return 0;
}