#include "jngen.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv);
  parseArgs(argc, argv);

  cout << "1\n100\n";
  auto poly = rndg.convexPolygon(100, 1e3);
  cout << poly << endl;

  return 0;
}