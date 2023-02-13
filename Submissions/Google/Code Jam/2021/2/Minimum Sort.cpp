#include <bits/stdc++.h>
using namespace std;

int queryMin(int l, int r) {
  cout << "M " << l << " " << r << endl;
  int res;
  cin >> res;
  assert(l <= res and res <= r);
  return res;
}

void swapElems(int i, int j) {
  assert(i != j);
  cout << "S " << i << " " << j << endl;
  int res;
  cin >> res;
  assert(res == 1);
}

void answer() {
  cout << "D" << endl;
  int res;
  cin >> res;
  assert(res == 1);
}

void solve(int cs, int n) {
  for (int l = 1, r = n; l < n; l++) {
    int m = queryMin(l, r);
    if (l != m) swapElems(l, m);
  }
  answer();
}

int main() {
  int t, n;
  cin >> t >> n;

  for (int cs = 1; cs <= t; cs++) solve(cs, n);

  return 0;
}