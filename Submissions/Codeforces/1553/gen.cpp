#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  const int N = 100, A = 5000;

  int n = rnd.next(N) + 1;
  cout << n << "\n";

  map<int, int> vis;
  for (int i = 0; i < n; i++) {
    if (i) cout << " ";
    while (true) {
      int a = rnd.next(A) + 1;
      if (vis.find(a) != vis.end()) continue;
      vis[a] = true;
      cout << a;
      break;
    }
  }
  cout << "\n";

  return 0;
}