#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  int n = rnd.next(1, 20);
  string s = rnd.next(string("[1*]{") + to_string(n) + string("}"));

  cout << n << "\n" << s << "\n";

  return 0;
}