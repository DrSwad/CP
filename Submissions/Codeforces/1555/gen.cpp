#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  const int N = 8, M = 10, W = 10;

  int n = rnd.next(N) + 1;
  int m = rnd.next(M - 1) + 2;
  cout << n << " " << m << "\n";

  for (int i = 0; i < n; i++) {
    int l = rnd.next(m - 1) + 1;
    int r = rnd.next(m - l) + l + 1;
    int w = rnd.next(W) + 1;
    cout << l << " " << r << " " << w << "\n";
  }

  return 0;
}