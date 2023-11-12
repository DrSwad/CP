#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  const int N = 6, K = 6;

  int n = rnd.next(2, N);
  int k = rnd.next(2, min(n, K));
  println(n, k);

  return 0;
}