#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  const int N = 10;
  int n = rnd.next(1, N);
  println(n);
  while (n--) {
    char from = 'a' + rnd.next(3);
    char to = 'a' + rnd.next(3);
    println(string(1, from) + string(1, to));
  }

  return 0;
}