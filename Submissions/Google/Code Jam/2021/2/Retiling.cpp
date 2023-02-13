#include <bits/stdc++.h>
using namespace std;

const int N = 15;

int rows, cols, flip_cost, swap_cost;
char tile[N][N];
char need[N][N];

int solve() {
  return 0;
}

int main() {
  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    scanf("%d %d %d %d", &rows, &cols, &flip_cost, &swap_cost);

    for (int r = 1; r <= rows; r++) {
      for (int c = 1; c <= cols; c++) {
        scanf(" %c", &tile[r][c]);
      }
    }

    for (int r = 1; r <= rows; r++) {
      for (int c = 1; c <= cols; c++) {
        scanf(" %c", &need[r][c]);
      }
    }

    printf("Case #%d: %d\n", solve());
  }

  return 0;
}