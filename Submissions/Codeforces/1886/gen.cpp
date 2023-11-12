#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = rnd.next(1, 10);
  println(t);

  while (t--) {
    println(rnd.next(1, 10));
  }

  return 0;
}