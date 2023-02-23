#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 5;
  println(t);

  while (t--) {
    int n = rnd.next(1, 10), m = rnd.next(1, 10), q = rnd.next(1, 100);
    println(n, m, q);
    for (int i = 0; i < n; i++) {
      vector<char> row(m);
      for (char &c : row) c = '0' + rnd.next(10);
      println(row);
    }
    while (q--) {
      int type = rnd.next(1, 2);
      if (type == 1) {
        int x1 = rnd.next(1, n), y1 = rnd.next(1, m), x2 = rnd.next(x1, n), y2 = rnd.next(y1, m);
        println(type, x1, y1, x2, y2);
      }
      else {
        int x = rnd.next(1, n), y = rnd.next(1, m);
        println(type, x, y);
      }
    }
  }

  return 0;
}