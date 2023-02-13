#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  const int N = 5, Q = 5, V = 5;

  int n = rnd.next(1, N);
  println(n);

  while (n--) {
    int l = rnd.next(1, V);
    int r = rnd.next(l, V);
    println(l, r);
  }

  int q = rnd.next(1, Q);
  println(q);

  while (q--) {
    println(rnd.next(1, V));
  }

  return 0;
}