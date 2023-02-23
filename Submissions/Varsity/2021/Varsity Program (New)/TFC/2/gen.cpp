#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  const int N = 5, M = 20, A = 5, V = 5;

  int n = N, m = rnd.next(1, M);
  println(n, m);

  vector<int> a(n);
  for (int &i : a) i = rnd.next(1, A);
  println(a);

  while (m--) {
    int t = rnd.next(1, 3);
    if (t == 1) {
      int x = rnd.next(1, n);
      int c = rnd.next(1, A);
      println(t, x, c);
    }
    else if (t == 2) {
      int x = rnd.next(1, n);
      int y = rnd.next(1, n);
      while (y == x) y = rnd.next(1, n);
      println(t, x, y);
    }
    else {
      int x = rnd.next(1, n);
      int y = rnd.next(1, n);
      int v = rnd.next(1, A);
      println(t, x, y, v);
    }
  }

  return 0;
}