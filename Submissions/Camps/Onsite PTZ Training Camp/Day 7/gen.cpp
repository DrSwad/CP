#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  const int N = 3000, M = 1e8;
  println(rnd.next(1, N), rnd.next(1, M));

  return 0;
}