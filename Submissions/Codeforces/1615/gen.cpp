#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  const int N = 6;
  int n = rnd.next(1, N);
  int k = rnd.next(1, n);
  println(n, k);

  for (int child = 2; child <= n; child++) {
    int parent = rnd.next(1, child - 1);
    println(parent, child);
  }

  return 0;
}