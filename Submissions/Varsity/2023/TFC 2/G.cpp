#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int x, y;
  cin >> x >> y;

  if (x == y) {
    cout << "0\n";
  }
  else if (x == 0) {
    if (y < 0) cout << abs(y) + 1 << "\n";
    else cout << y << "\n";
  }
  else if (x < 0) {
    if (y <= 0) {
      if (y < x) cout << abs(abs(y) - abs(x)) + 2 << "\n";
      else cout << abs(abs(y) - abs(x)) << "\n";
    }
    else {
      cout << abs(abs(y) - abs(x)) + 1 << "\n";
    }
  }
  else if (x > 0) {
    if (y > 0) {
      if (y > x) cout << abs(abs(y) - abs(x)) << "\n";
      else cout << abs(abs(y) - abs(x)) + 2 << "\n";
    }
    else {
      cout << abs(abs(y) - abs(x)) + 1 << "\n";
    }
  }

  return 0;
}