#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  const int N = 4, R = 7, A = 5;

  int n = N;
  int r = 3 + rnd.next(R - 2);
  cout << n << " " << r << "\n";

  for (int i = 0; i < n; i++) {
    if (i) cout << " ";
    cout << 2 + rnd.next(A - 1);
  }
  cout << "\n";

  return 0;
}