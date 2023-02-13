#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  const int N = 5, A = 10;

  int t = 5;
  cout << t << "\n";

  while (t--) {
    int n = N;
    cout << n << "\n";
    while (n--) cout << rnd.next(2 * A + 1) - A << " ";
    cout << "\n";
  }

  return 0;
}