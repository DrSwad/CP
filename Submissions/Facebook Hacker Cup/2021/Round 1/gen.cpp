#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  cout << "1\n";

  const int N = 10;

  int n = rnd.next(N) + 1;
  cout << n << "\n";
  cout << rnd.next("[FXO]");
  if (n) cout << rnd.next("[FXO.]{%d}", n - 1);
  cout << "\n";

  return 0;
}