#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<string> grid(n);
  for (auto &row : grid) cin >> row;

  vector<vector<int>> right_streak(n, vector<int>(n));
  for (int i = 0; i < n; i++) {
    right_streak[i][n - 1] = 1;
    for (int j = n - 2; j >= 0; j--) {
      right_streak[i][j] = 1;
      if (grid[i][j] == grid[i][j + 1]) {
        right_streak[i][j] += right_streak[i][j + 1];
      }
    }
  }

  int ans = 0;

  function<bool(int, int, int)> check_zebra_rows = [&](int row_u, int col_l, int col_r) {
    if (row_u < 0) return false;
    int row_d = row_u + 1;
    if (row_d >= n) return false;
    assert(0 <= col_l and col_l <= col_r and col_r <= n - 1);
    if (right_streak[row_u][col_l] < col_r - col_l + 1) return false;
    if (right_streak[row_d][col_l] < col_r - col_l + 1) return false;
    if (grid[row_u][col_l] == grid[row_d][col_l]) return false;
    return true;
  };

  function<void(int, int, int, int)> consider_rect = [&](int row_u, int row_d, int col_l, int col_r) {
    if (check_zebra_rows(row_u - 1, col_l, col_r)) return;
    if (check_zebra_rows(row_d, col_l, col_r)) return;
    ans++;
  };

  function<vector<pair<int, int>>(const vector<int>&)> get_ranges = [&](const vector<int> &status) {
    vector<pair<int, int>> ret;
    for (int l = 0; l < n; ) {
      if (status[l] == -1) l++;
      else {
        int r = l;
        while (r < n and status[r] == status[l]) r++;
        ret.emplace_back(l, r - 1);
        l = r;
      }
    }
    return ret;
  };

  for (int row_u = 0; row_u < n; row_u++) {
    vector<int> status(n);
    for (int col = 0; col < n; col++) {
      status[col] = grid[row_u][col] == 'W';
    }

    auto ranges = get_ranges(status);
    for (auto [col_l, col_r] : ranges) {
      consider_rect(row_u, row_u, col_l, col_r);
    }

    for (int row_d = row_u + 1; row_d < n; row_d++) {
      for (int col = 0; col < n; col++) {
        if (status[col] == -1 or grid[row_d][col] == grid[row_d - 1][col]) {
          status[col] = -1;
        }
      }

      auto ranges = get_ranges(status);
      for (auto [col_l, col_r] : ranges) {
        consider_rect(row_u, row_d, col_l, col_r);
      }
    }
  }

  cout << ans << "\n";
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