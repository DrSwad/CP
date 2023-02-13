#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  cout << "1\n";

  const int N = 4, A = 5;

  int n = rnd.next(N) + 1;
  n = 4;
  cout << n << "\n";

  while (n--) {
    int a = rnd.next(A);
    int b = a + rnd.next(A - a);
    cout << a << " " << b << "\n";
  }

  return 0;
}