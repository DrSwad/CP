#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  const int N = 5;

  int n = rnd.next(1, N);
  println(n);

  vector<int> p(n), q(n);
  iota(p.begin(), p.end(), 1);
  iota(q.begin(), q.end(), 1);

  shuffle(p.begin(), p.end());
  shuffle(q.begin(), q.end());

  println(p);
  println(q);

  return 0;
}