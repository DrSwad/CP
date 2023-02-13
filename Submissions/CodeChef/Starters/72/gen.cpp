#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  const int T = 1;
  int t = rnd.next(1, T);
  println(t);

  while (t--) {
    const int N = 6;
    int n = rnd.next(1, N);
    println(n);

    const int A = 4;
    vector<int> a(n);
    for (int &i : a) i = rnd.next(1, A);
    println(a);
  }

  return 0;
}