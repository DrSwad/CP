#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  const int N = 100;

  int n = rnd.next(2, N);
  println(n);
  println(rnd.next("[123]{%d}", n));

  return 0;
}