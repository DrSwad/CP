#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  const int T = 100;
  const int N = 15;
  const int K = 10;
  const int Q = 1000;

  int t = rnd.next(1, T);
  println(t);

  while (t--) {
    int n = rnd.next(1, N), k = rnd.next(1, K);
    println(n, k);

    for (int row = 0; row < n; row++) {
      println(rnd.next("[01]{" + to_string(n) + "}"));
    }

    int q = rnd.next(1, Q);
    println(q);

    while (q--) {
      int len = n * n * k * k;
      int l = rnd.next(0, len - 1);
      int r = rnd.next(l, len - 1);
      println(l, r);
    }
  }

  return 0;
}