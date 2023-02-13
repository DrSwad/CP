#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char*argv[]) {
  registerGen(argc, argv, 1);

  const int T = 1, N = 8;

  int t = rnd.next(T) + 1;
  cout << t << endl;

  while (t--) {
    int n = rnd.next(N) + 1;
    cout << n << endl;
    while (n--) {
      cout << rnd.next(2) * 2 - 1 << " ";
    }
    puts("");
  }

  return 0;
}