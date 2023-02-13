#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char*argv[]) {
  registerGen(argc, argv, 1);

  const int T = 5, N = 10;

  int t = rnd.next(T) + 1;
  cout << t << endl;

  while (t--) {
    cout << rnd.next("[a-b]{1, %d}", N) << "\n";
    cout << rnd.next("[a-b]{1, %d}", N) << "\n";
  }

  return 0;
}