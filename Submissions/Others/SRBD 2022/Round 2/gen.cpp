#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 10;
  println(t);

  while (t--) {
    int n = 4;
    println(n);

    vector<vector<pair<int, bool>>> e(n, vector<pair<int, bool>>(n));

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (i == j) cout << "(0, T) ";
        else {
          int r;
          bool b;
          r = j < i ? e[j][i].first : rnd.next(0, 10);
          b = j < i ? !e[j][i].second : rnd.next(10) >= 5;
          e[min(i, j)][max(i, j)] = {r, b};
          cout << "(" << r << ", " << (b ? 'T' : 'F') << ") ";
        }
      }
      cout << "\n";
    }
  }

  return 0;
}