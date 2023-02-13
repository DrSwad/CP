#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  long long x, y;
  cin >> x >> y;

  int len = 0;
  long long at = x;
  while (at <= y) {
    len++;
    at *= 2;
  }

  cout << len << "\n";

  return 0;
}