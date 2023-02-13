#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  const int N = 10, A = 3, Q = 10;

  int n = rnd.next(1, N);
  println(n);

  string s(n, '0');
  for (char &c : s) c = 'a' + rnd.next(A);
  println(s);

  int q = rnd.next(1, Q);
  println(q);

  while (q--) {
    int t_len = (n * n + 1) / 2;
    int l = rnd.next(1, t_len);
    int r = rnd.next(l, t_len);
    println(l, r);
  }

  return 0;
}