#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  const int N = 15;

  int n = rnd.next(1, N);
  int k = rnd.next(0, min(20, n - 1));
  println(n, k);

  for (int node = 2; node <= n; node++) {
    int parent = rnd.next(1, node - 1);
    println(parent, node);
  }

  return 0;
}