#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  const int N = 5;
  const int A = 10;

  int n = rnd.next(N) + 1;
  cout << n << "\n";

  for (int i = 0; i < n; i++) {
    int a = rnd.next(A) + 1;
    int b = rnd.next(A) + 1;
    cout << a << " " << b << "\n";
  }

  return 0;
}