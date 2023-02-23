#include <bits/stdc++.h>
using namespace std;

int D = 10;
int dx[] = {0, 1};
int dy[] = {1, 0};

int main() {
  int n;
  cin >> n;

  vector<vector<int>> freq(D, vector<int>(D, 0));
  bool flag = true;

  for (int i = 0; i < n; i++) {
    int d, l, r, c;
    cin >> d >> l >> r >> c;
    r--, c--;

    for (int x = r, y = c; l; l--) {
      if (x < 0 or D <= x or y < 0 or D <= y) {
        flag = false;
        break;
      }
      freq[x][y]++;
      x += dx[d];
      y += dy[d];
    }
  }

  for (int i = 0; i < D; i++) {
    for (int j = 0; j < D; j++) {
      if (freq[i][j] > 1) {
        flag = false;
      }
    }
  }

  puts(flag ? "Y" : "N");

  return 0;
}