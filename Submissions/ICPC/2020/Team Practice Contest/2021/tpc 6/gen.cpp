#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  const int N = 5;
  int n = rnd.next(N - 1) + 2;
  int l = rnd.next(n) + 1;
  int r = rnd.next(n - l + 1) + l;
  string s = rnd.next("[a-z]{%d}", n);

  cout << n << " " << l << " " << r << "\n" << s << "\n";

  return 0;
}