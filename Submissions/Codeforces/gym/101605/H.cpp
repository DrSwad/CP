#include <bits/stdc++.h>
using namespace std;

// front = f
// back = 1
// top = 2
// bottom = 3
// right = 4
// left = 5

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector cell(2 * n, vector(6, -1));
  cin >> cell[0][0] >> cell[1][0];
  for (int i = 0; i < n; i++) {
    cin >> cell[i * 2][2] >> cell[i * 2 + 1][2];
    cin >> cell[i * 2 + 1][4];
    cin >> cell[i * 2 + 1][3] >> cell[i * 2][3];
    cin >> cell[i * 2][5];
  }
  cin >> cell[2 * (n - 1)][1] >> cell[2 * (n - 1) + 1][1];

  return 0;
}