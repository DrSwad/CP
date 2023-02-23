#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  const int N = 4, K = 8;

  // int n = rnd.next(1, N), k = rnd.next(1, K);
  int n = 3e6, k = 1e9;
  println(n, k);

  println(rnd.next("[01]{%d}", n));

  return 0;
}