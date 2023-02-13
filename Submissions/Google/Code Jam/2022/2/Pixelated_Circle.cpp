#include <bits/stdc++.h>
using namespace std;

int r;
vector<string> grid;

void set_pixel_to_black(int x, int y) {
  grid[r + x][r + y] = '#';
}

void draw_circle_perimeter(int R) {
  for (int x = -R; x <= R; x++) {
    int y = round(sqrt(R * R - x * x));   // round to nearest integer, breaking ties towards zero
    set_pixel_to_black(x, y);
    set_pixel_to_black(x, -y);
    set_pixel_to_black(y, x);
    set_pixel_to_black(-y, x);
  }
}

void draw_circle_filled(int R) {
  for (int x = -R; x <= R; x++) {
    for (int y = -R; y <= R; y++) {
      if (round(sqrt(x * x + y * y)) <= R) {
        set_pixel_to_black(x, y);
      }
    }
  }
}

void draw_circle_filled_wrong(int R) {
  for (int r = 0; r <= R; r++) {
    draw_circle_perimeter(r);
  }
}

void test_case() {
  cin >> r;

  grid.assign(2 * r + 1, string(2 * r + 1, '.'));
  draw_circle_filled(r);
  int tot1 = 0;
  for (string &row : grid) {
    tot1 += count(row.begin(), row.end(), '#');
  }

  grid.assign(2 * r + 1, string(2 * r + 1, '.'));
  draw_circle_filled_wrong(r);
  int tot2 = 0;
  for (string &row : grid) {
    tot2 += count(row.begin(), row.end(), '#');
  }

  cout << abs(tot1 - tot2) << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}