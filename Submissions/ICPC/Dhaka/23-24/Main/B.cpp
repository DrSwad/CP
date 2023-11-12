#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int t;
  cin >> t;

  while (t--) {
    char a, b;
    cin >> a >> b;

    int x = a - '!';
    int y = b - '!';

    int tot = 126 - 33 + 1;

    for (int r = 1; r <= tot; r++) {
      if (x % r == y % r) {
        cout << r << " " << (tot + r - 1) / r << "\n";
      }
    }

    cout << "\n";
  }

  return 0;
}