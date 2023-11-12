#include <bits/stdc++.h>
using namespace std;

int rec(int a) {
  if (a == 1) return a * a;
  return rec(a - 1);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cout << rec(1e7) << endl;

  return 0;
}