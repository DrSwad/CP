#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  const int N = 100;
  int n = N;
  println(n);

  const int X = 1e2;
  for (int i = 0; i < n; i++) {
    int l = rnd.next(1, X);
    int r = rnd.next(l, X);
    println(l, r);
  }

  const int Q = 100;
  int q = Q;
  println(q);
  while (q--) {
    println(rnd.next(1, X));
  }

  return 0;
}