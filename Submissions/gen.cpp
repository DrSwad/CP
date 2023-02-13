#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  println(t);

  const int N = 1e4;
  int n = rnd.next(1, N);
  println(n);

  const int C = 1e5;
  for (int i = 2; i <= n; i++) {
    println(i, rnd.next(1, i - 1), rnd.next(1, C));
  }

  int Q = 1e4;
  int q = Q;
  while (q--) {
    string type = rnd.next(10) < 5 ? "DIST" : "KTH";
    if (type == "DIST") {
      println(type, rnd.next(1, n), rnd.next(1, n));
    }
    else {
      println(type, rnd.next(1, n), rnd.next(1, n), rnd.next(1, n));
    }
  }
  println("DONE");

  return 0;
}