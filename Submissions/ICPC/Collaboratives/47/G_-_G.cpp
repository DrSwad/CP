#include <bits/stdc++.h>
using namespace std;

int dr[] = {1, 0, -1, 0};
int dc[] = {0, -1, 0, 1};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int rows, cols;
  cin >> rows >> cols;

  vector<string> grid(rows);
  for (string &row : grid) cin >> row;

  vector<vector<int>> dist(rows, vector<int>(cols, rows + cols + 10));
  queue<pair<int, int>> q;

  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < cols; c++) {
      if (grid[r][c] == '#') {
        dist[r][c] = 0;
        q.push({r, c});
      }
    }
  }

  int ans = 0;
  while (!q.empty()) {
    auto [r, c] = q.front();
    q.pop();
    ans = max(ans, dist[r][c]);

    for (int di = 0; di < 4; di++) {
      int nr = r + dr[di];
      int nc = c + dc[di];
      if (0 <= nr and nr < rows and 0 <= nc and nc < cols) {
        int nd = dist[r][c] + 1;
        if (dist[nr][nc] > nd) {
          dist[nr][nc] = nd;
          q.push({nr, nc});
        }
      }
    }
  }

  cout << ans << "\n";

  return 0;
}