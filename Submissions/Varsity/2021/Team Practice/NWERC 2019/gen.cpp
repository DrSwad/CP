#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  const int N = 1e4, H = 1e9, Q = 50, G = 1000;

  // int n = rnd.next(2, N);
  int n = N;
  // int q = rnd.next(1, Q);
  int q = Q;
  println(n, q);

  vector<int> h(n + 1);
  for (int &i : h) i = rnd.next(H + 1);
  println(h);

  while (q--) {
    int g = rnd.next(-G, G);
    printf("%02d.%1d\n", g / 10, abs(g % 10));
  }

  return 0;
}