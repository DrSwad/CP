#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  println(t);

  int n = 4;
  println(n);

  const int A = 5;
  vector<vector<int>> mat(n, vector<int>(n));
  for (auto &row : mat) {
    for (int &cell : row) {
      cell = rnd.next(1, A);
    }
  }

  for (auto row : mat) println(row);

  return 0;
}