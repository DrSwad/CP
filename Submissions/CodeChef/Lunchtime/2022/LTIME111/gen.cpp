#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  println(t);
  while (t--) {
    int n = 5;
    println(n);
    vector<int> a(n);
    for (int &i : a) i = rnd.next(-5, 5);
    println(a);
  }

  return 0;
}