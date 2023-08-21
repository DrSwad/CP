#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  const int N = 100, A = 100;

  int n = rnd.next(1, N);
  int a = rnd.next(1, A);
  int b = rnd.next(1, A);
  int c = rnd.next(1, A);
  int g = gcd(a, gcd(b, c));
  int x = g * rnd.next(1, (a * n + b * n + c * n) / g);

  println(n, a, b, c, x);

  return 0;
}