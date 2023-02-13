#include "jngen.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char*argv[]) {
  registerGen(argc, argv);
  parseArgs(argc, argv);

  const int T = 1, N = 10;

  int t = rnd.next(T) + 1;
  cout << t << endl;

  while (t--) {
    int n = 3 + rnd.next(N - 3 + 1);
    cout << n << endl;
    cout << Tree::random(n).add1() << endl;
  }

  return 0;
}