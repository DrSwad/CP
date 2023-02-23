#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  cout << "1\n";

  const int L = 10;

  int n = 5, q = 5;
  cout << n << " " << q << "\n";

  vector<string> s(n);
  for (int i = 0; i < n; i++) {
    s[i] = rnd.next("[abc]{%d}", rnd.next(L) + 1);
  }

  for (int i = 0; i < n; i++) {
    cout << s[i] << "\n";
  }

  while (q--) {
    cout << s[rnd.next(n)] << " ";
    cout << s[rnd.next(n)] << "\n";
  }

  return 0;
}