#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  const int N = 10;

  int t = 5;
  cout << t << "\n";

  while (t--) {
    for (int i = 0; i < 3; i++) {
      int len = rnd.next(N) + 1;
      cout << rnd.next("[a-d]{%d}", len) << "\n";
    }
  }

  return 0;
}