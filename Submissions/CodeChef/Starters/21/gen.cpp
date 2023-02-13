#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  const int T = 5, N = 5, A = 5, Q = 5;

  int t = T;
  cout << t << "\n";

  while (t--) {
    int n = N;
    cout << n << "\n";

    for (int i = 0; i < n; i++) {
      if (i) cout << " ";
      cout << 1 + rnd.next(N);
    }
    cout << "\n";

    int q = rnd.next(Q);
    cout << q << "\n";

    for (int i = 0; i < q; i++) {
      int u = 1 + rnd.next(N);
      int v = 1 + rnd.next(N);
      cout << u << " " << v << "\n";
    }
  }

  return 0;
}