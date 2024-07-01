#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  const int T = 1;
  const int N = 10;
  const int A = 10;

  int t = rnd.next(1, T);
  println(t);

  while (t--) {
    int n = rnd.next(1, N);
    int k = rnd.next(0, A);
    println(n, k);

    vector<int> f(n), d(n);
    for (int &i : f) i = rnd.next(1, A);
    for (int &i : d) i = rnd.next(1, A);
    println(f);
    println(d);
  }

  return 0;
}