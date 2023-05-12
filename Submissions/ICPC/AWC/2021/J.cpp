#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<string> grid(n);
  for (auto &row : grid) cin >> row;

  const int dim_r = 3, dim_c = 7;

  function<bool(int, int, int, int)> check_corners = [&](int r_u, int r_d, int c_l, int c_r) {
    char c = grid[r_u][c_l];
    if (grid[r_u][c_l] != c) return false;
    if (grid[r_u][c_r] != c) return false;
    if (grid[r_d][c_l] != c) return false;
    if (grid[r_d][c_r] != c) return false;
    return true;
  };

  function<array<int, 4>(array<int, 3>, array<int, 7>)> find_rect = [&](array<int, 3> rows, array<int, 7> cols) {
    for (int r_u = 0; r_u < dim_r - 1; r_u++) {
      for (int r_d = r_u + 1; r_d < dim_r; r_d++) {
        for (int c_l = 0; c_l < dim_c - 1; c_l++) {
          for (int c_r = c_l + 1; c_r < dim_c; c_r++) {
            if (check_corners(rows[r_u], rows[r_d], cols[c_l], cols[c_r])) {
              return array<int, 4>{rows[r_u], rows[r_d], cols[c_l], cols[c_r]};
            }
          }
        }
      }
    }
    assert(false);
  };

  int need = max(1, (n * n) / 7 - 35);

  for (int row_u = 0; row_u + dim_r <= n and need; row_u += dim_r) {
    array<int, dim_r> rows = {row_u, row_u + 1, row_u + 2};

    array<int, dim_c> cols;
    iota(cols.begin(), cols.begin() + 5, 0);
    cols[5] = cols[6] = -1;

    for (int col = 5; col + 2 <= n and need; col += 2) {
      for (int i = 0; i < dim_c; i++) if (cols[i] == -1) { cols[i] = col; break; }
      for (int i = 0; i < dim_c; i++) if (cols[i] == -1) { cols[i] = col + 1; break; }
      auto [r_u, r_d, c_l, c_r] = find_rect(rows, cols);
      cout << r_u + 1 << " " << c_l + 1;
      cout << " " << r_u + 1 << " " << c_r + 1;
      cout << " " << r_d + 1 << " " << c_l + 1;
      cout << " " << r_d + 1 << " " << c_r + 1;
      cout << "\n";
      need--;

      *find(cols.begin(), cols.end(), c_l) = -1;
      *find(cols.begin(), cols.end(), c_r) = -1;
    }
  }

  assert(need == 0);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}