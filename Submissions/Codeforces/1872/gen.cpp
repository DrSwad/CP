#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  const int T = 1e4;
  const int N = 2e5;
  const int A = 1e9;

  int t = rnd.next(1, T);
  println(t);

  int tot_n = 0;
  while (t--) {
    int n = rnd.next(2, N - tot_n - 2 * t);
    println(n);

    vector<int> a(n);
    for (int &i : a) {
      int type = rnd.wnext(4, -5);
      if (type) i = rnd.next(1, A);
      else i = 1;
    }
    println(a);

    tot_n += n;
  }

  return 0;
}