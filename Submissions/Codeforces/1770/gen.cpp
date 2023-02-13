#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  const int N = 5;
  int n = rnd.next(2, N);
  int k = rnd.next(2, n);
  println(n, k);

  {
    vector<int> v(n);
    iota(v.begin(), v.end(), 1);
    shuffle(v.begin(), v.end());
    println(vector<int>(v.begin(), v.begin() + k));
  }

  for (int i = 2; i <= n; i++) {
    println(i, rnd.next(1, i - 1));
  }

  return 0;
}