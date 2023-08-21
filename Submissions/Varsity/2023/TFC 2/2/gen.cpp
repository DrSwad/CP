#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  const int N = 3, Q = 3, A = 3;

  int t = 1;
  println(t);

  int n = rnd.next(1, N);
  int q = rnd.next(1, Q);
  println(n, q);

  int a = rnd.next(0, A);
  int b = rnd.next(-A, A);
  println(a, b);

  vector<int> c(n);
  for (int &i : c) c[i] = rnd.next(-A, A);
  println(c);

  for (int i = 2; i <= n; i++) {
    int p = rnd.next(1, i - 1);
    println(p, i);
  }

  while (q--) {
    int type = rnd.next(1, 2);
    if (type == 1) {
      int u = rnd.next(1, n);
      int v = rnd.next(1, n);
      int w = rnd.next(1, A);
      println(type, u, v, w);
    }
    else {
      int u = rnd.next(1, n);
      int v = rnd.next(1, n);
      println(type, u, v);
    }
  }

  return 0;
}