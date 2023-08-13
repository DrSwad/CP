#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  println(t);

  const int N = 3;
  int n = rnd.next(1, N);
  int k = rnd.next(1, n);
  println(n, k);

  const int A = 5;
  vector<int> a(n), b(n);
  for (int &i : a) i = rnd.next(-A, A);
  for (int &i : b) i = rnd.next(-A, A);
  println(a);
  println(b);

  return 0;
}