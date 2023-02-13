#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  const int N = 5;
  int n = rnd.next(2, N);
  int k = rnd.next(2, n);
  println(n, k);

  const int A = 1e9;
  vector<int> a(n);
  for (int &i : a) i = rnd.next(1, A);
  println(a);

  return 0;
}