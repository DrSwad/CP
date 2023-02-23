#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char*argv[]) {
  registerGen(argc, argv, 1);

  const int N = 10;

  int n = rnd.next(N) + 1;
  vector<int> a = rnd.perm(n);
  for (int &i : a) i++;

  puts("1");
  printf("%d\n", n);
  for (int &i : a) printf("%d ", i);
  puts("");

  return 0;
}