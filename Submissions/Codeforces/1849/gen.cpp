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

  vector<int> p = rnd.perm(n);
  for (int &i : p) i++;
  println(p);

  return 0;
}