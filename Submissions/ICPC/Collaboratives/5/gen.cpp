#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  const long long N = 5000, M = 5000, A = 1e14, Q = 5, MOD = 1e14;
  int n = rnd.next(N) + 1;
  int m = rnd.next(M) + 1;
  cout << n << " " << m << endl;
  for (int i = 0; i < n; i++) {
    printf("%lld ", rnd.next(A) + 1);
  }
  puts("");
  for (int i = 0; i < m; i++) {
    printf("%lld ", rnd.next(A) + 1);
  }
  puts("");

  int q = rnd.next(Q) + 1;
  cout << q << endl;
  while (q--) {
    printf("%lld\n", rnd.next(MOD) + 1);
  }

  return 0;
}