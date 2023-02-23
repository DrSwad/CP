#include <bits/stdc++.h>
using namespace std;

int digits[4][3] = {
  {1, 2, 3},
  {4, 5, 6},
  {7, 8, 9},
  {-1, 0, -1},
};

bool check(int n) {
  string sn = to_string(n);
  int px = -1, py = -1;

  for (char cd : sn) {
    int d = cd - '0';
    int cx, cy;

    for (int x = 0; x < 4; x++) {
      for (int y = 0; y < 3; y++) {
        if (digits[x][y] == d) {
          cx = x, cy = y;
        }
      }
    }

    if (cx < px or cy < py) return false;
    px = cx, py = cy;
  }

  return true;
}

int main() {
  vector<bool> valid(1000);
  for (int n = 1; n < 1000; n++) {
    valid[n] = check(n);
    if (n < 100) debug() << name(n) name(valid[n]);
  }

  int t;
  cin >> t;

  while (t--) {
    int k;
    scanf("%d", &k);

    for (int d = 0; ; d++) {
      if (valid[k - d]) {
        printf("%d\n", k - d);
        break;
      }
      if (valid[k + d]) {
        printf("%d\n", k + d);
        break;
      }
    }
  }

  return 0;
}