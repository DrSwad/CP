#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  println(t);

  while (t--) {
    int n = rnd.next(1, 5);
    int q = rnd.next(1, 5);
    println(n, q);

    vector<int> a(n), b(n);
    for (int &i : a) i = rnd.next(0, 5);
    for (int &i : b) i = rnd.next(0, 5);
    println(a);
    println(b);

    while (q--) {
      int l = rnd.next(1, n);
      int r = rnd.next(l, n);
      println(l, r);
    }
  }

  return 0;
}