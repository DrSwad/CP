#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = rnd.next(1, 10);
  println(t);

  // int N = atoi(argv[1]);
  int N = 5;
  while (t--) {
    for (int it = 0; it < 2; it++) {
      int n = rnd.next(1, N);
      println(rnd.next("[a-b]{%d}", n));
    }
  }

  return 0;
}