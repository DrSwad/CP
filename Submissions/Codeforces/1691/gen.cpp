#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  const int N = 5;
  const int X = 10;

  cout << "1\n";

  int n = rnd.next(1, N);
  cout << n << "\n";

  while (n--) {
    int c = rnd.next(2);
    int l = rnd.next(-X, X);
    int r = rnd.next(l, X);
    cout << c << " " << l << " " << r << "\n";
  }

  return 0;
}