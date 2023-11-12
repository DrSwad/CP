#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  const int T = 1;
  const int N = 1e2;
  const int M = 1e5;

  int t = rnd.next(1, T);
  println(t);

  while (t--) {
    int n = rnd.next(1, N);
    int m = rnd.next(M, M);
    println(n, m);
  }

  return 0;
}