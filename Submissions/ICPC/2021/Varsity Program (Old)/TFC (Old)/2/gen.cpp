#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n = 10, q = 10, X = 100;

  map<pair<int, int>, int> used;
  cout << n << " " << q << "\n";

  for (int i = 0; i < n + q; i++) {
    while (true) {
      int x = rnd.next(2 * X + 1) - X;
      int y = rnd.next(2 * X + 1) - X;
      if (used.find(make_pair(x, y)) != used.end()) continue;
      used[{x, y}]++;
      cout << x << " " << y << "\n";
      break;
    }
  }

  return 0;
}