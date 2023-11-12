#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  const int N = 100, A = 10, Q = 100;

  int t = 100;
  println(t);

  while (t--) {
    int n = rnd.next(1, N);
    println(n);

    vector<int> a(n);
    for (int &i : a) rnd.next(1, A);
    println(a);

    int q = rnd.next(1, Q);
    println(q);

    while (q--) {
      int i, x;
      i = rnd.next(1, n);
      x = rnd.next(1, A);
      println(i, x);
    }
  }

  return 0;
}