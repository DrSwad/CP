#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  const int N = 10, A = 20;
  int n = rnd.next(1, N);
  vector<int> a(n);
  for (int &i : a) i = rnd.next(1, A);
  println(1);
  println(n);
  println(a);

  return 0;
}