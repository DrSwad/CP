#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  const int T = 5;
  int t = rnd.next(1, T);
  println(t);

  const int N = 3;
  const int C = 2;
  const int Q = 5;

  while (t--) {
    int n1 = rnd.next(N, N);
    int n2 = rnd.next(N, N);
    string s1, s2;
    while (n1--) s1 += 'a' + rnd.next(C);
    while (n2--) s2 += 'a' + rnd.next(C);
    println(s1);
    println(s2);

    int q = rnd.next(Q, Q);
    println(q);

    while (q--) {
      int type = rnd.next(1, 3);
      if (type == 1 or type == 2) {
        int L = 1, R = type == 1 ? s1.length() : s2.length();
        int l = rnd.next(L, R);
        int r = rnd.next(l, R);
        char c = 'a' + rnd.next(C);
        println(type, l, r, c);
      }
      else {
        int l1 = rnd.next(1, (int)s1.length());
        int r1 = rnd.next(l1, (int)s1.length());
        int l2 = rnd.next(1, (int)s2.length());
        int r2 = rnd.next(l2, (int)s2.length());
        println(type, l1, r1, l2, r2);
      }
    }
  }

  return 0;
}