#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  int T = 1;
  println(T);

  const int N = 10, M = 10;
  int n = rnd.next(2, N), m = rnd.next(1, M);
  int s = rnd.next(1, n), t = rnd.next(1, n);
  while (t == s) t = rnd.next(1, n);
  println(n, m, s, t);

  const int W = 10, C = 2;
  while (m--) {
    int u = rnd.next(1, n), v = rnd.next(1, n);
    while (v == u) v = rnd.next(1, n);
    int w = rnd.next(0, W);
    char c = 'a' + rnd.next(C);
    println(u, v, w, c);
  }

  return 0;
}