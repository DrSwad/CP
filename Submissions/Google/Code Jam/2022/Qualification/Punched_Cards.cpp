#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int r, c;
  cin >> r >> c;

  for (int i = 0; i < r; i++) {
    cout << (i == 0 ? '.' : '+');
    for (int j = 0; j < 2 * c; j++) {
      if (j % 2 == 0) {
        cout << (j == 0 and i == 0 ? '.' : '-');
      }
      else cout << '+';
    }
    cout << "\n";

    cout << (i == 0 ? '.' : '|');
    for (int j = 0; j < 2 * c; j++) {
      if (j % 2 == 0) cout << '.';
      else cout << '|';
    }
    cout << "\n";
  }

  cout << '+';
  for (int j = 0; j < 2 * c; j++) {
    cout << (j % 2 == 0 ? '-' : '+');
  }
  cout << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ":\n";
    test_case();
  }

  return 0;
}