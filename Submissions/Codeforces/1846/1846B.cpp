#include <bits/stdc++.h>
using namespace std;

void test_case() {
  vector<string> grid(3);
  for (string &row : grid) cin >> row;

  vector<int> dr{0, 1, 1, -1};
  vector<int> dc{{1, 0, 1, 1}};

  auto is_valid =
    [&](int r, int c) {
      return 0 <= r and r < 3 and 0 <= c and c < 3;
    };

  for (int dir = 0; dir < dr.size(); dir++) {
    for (int st_r = 0; st_r < 3; st_r++) {
      for (int st_c = 0; st_c < 3; st_c++) {
        int got = 0;
        for (int at_r = st_r, at_c = st_c; is_valid(at_r, at_c); at_r += dr[dir], at_c += dc[dir]) {
          if (grid[at_r][at_c] != grid[st_r][st_c]) break;
          got++;
        }
        if (got >= 3 and grid[st_r][st_c] != '.') {
          cout << grid[st_r][st_c] << "\n";
          return;
        }
      }
    }
  }

  cout << "DRAW" << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}