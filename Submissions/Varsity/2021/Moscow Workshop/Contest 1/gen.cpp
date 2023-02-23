#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  const int N = 10, A = 5;

  int n = N;
  cout << n << endl;

  while (n--) {
    cout << rnd.next(A) + 1 << " ";
  }

  cout << endl;

  return 0;
}