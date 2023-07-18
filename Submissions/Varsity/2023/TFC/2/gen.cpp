#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int N = 10;
const long long A = 7;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n = rnd.next(1, N);
  println(n);

  vector<long long> a(n);
  for (auto &i : a) i = rnd.next(1ll, A);
  println(a);

  return 0;
}