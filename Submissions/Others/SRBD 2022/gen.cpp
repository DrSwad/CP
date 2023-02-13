#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  println(1);
  println(1e5);
  int n = 1e5;
  for (int i = 1; i <= n; i++) {
    println(rnd.next(i * 10, (int)1e9), rnd.next(1, (int)1e9));
  }

  return 0;
}