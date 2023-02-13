#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n = 10;
  println(n);

  vector<int> a(n);
  for (int &i : a) i = rnd.next(1, 20);
  println(a);

  return 0;
}