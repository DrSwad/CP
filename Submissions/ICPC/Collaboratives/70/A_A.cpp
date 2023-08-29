#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int x, y;
  while (cin >> x >> y, x or y) {
    if (x + y == 13) cout << "Never speak again.\n";
    else if (x > y) cout << "To the convention.\n";
    else if (x < y) cout << "Left beehind.\n";
    else cout << "Undecided.\n";
  }

  return 0;
}