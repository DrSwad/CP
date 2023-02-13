#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  const int N = 20, A = 100;
  cout << "1\n";

  int n = rnd.next(N) + 1;
  cout << n << "\n";

  for (int i = 1; i <= n; i++) {
    cout << rnd.next(A) + 1 << " ";
  }
  cout << "\n";

  return 0;
}