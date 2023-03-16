#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
int dr[] = {0, -1, 0, 1};
int dc[] = {1, 0, -1, 0};

int bfs(const vector<string> &grid, int player, int toss_winner) {
  int rows = grid.size(), cols = grid[0].size();
  int st_row, st_col;
  int en_row, en_col;

  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < cols; c++) {
      if (grid[r][c] == 'D') en_row = r, en_col = c;
      if (grid[r][c] == '1' + player) st_row = r, st_col = c;
    }
  }

  vector<vector<int>> dist(rows, vector<int>(cols, INF));
  queue<pair<int, int>> q;

  dist[st_row][st_col] = player == toss_winner ? -1 : 0;
  q.push({st_row, st_col});

  while (!q.empty()) {
    auto [at_r, at_c] = q.front();
    q.pop();

    int d = dist[at_r][at_c] + 2;

    auto valid = [&](int nxt_r, int nxt_c) {
      if (nxt_r < 0 or rows - 1 < nxt_r) return false;
      if (nxt_c < 0 or cols - 1 < nxt_c) return false;
      if (abs(at_r - nxt_r) > d) return false;
      if (abs(at_c - nxt_c) > d) return false;
      if (grid[nxt_r][nxt_c] == '#') return false;
      return true;
    };

    for (int dir = 0; dir < 4; dir++) {
      for (int nxt_r = at_r, nxt_c = at_c; valid(nxt_r, nxt_c); nxt_r += dr[dir], nxt_c += dc[dir]) {
        if (dist[nxt_r][nxt_c] == INF) {
          dist[nxt_r][nxt_c] = d;
          q.emplace(nxt_r, nxt_c);
        }
      }
    }
  }

  return dist[en_row][en_col];
}

void test_case() {
  int rows, cols, toss_winner;
  cin >> rows >> cols >> toss_winner;
  toss_winner--;

  vector<string> grid(rows);
  for (string &row : grid) cin >> row;

  int dist[2];
  dist[0] = bfs(grid, 0, toss_winner);
  dist[1] = bfs(grid, 1, toss_winner);

  if (dist[0] == INF and dist[1] == INF) cout << "IMPOSSIBLE\n";
  else if (dist[0] < dist[1]) cout << "Saif\n";
  else if (dist[0] > dist[1]) cout << "Sabi\n";
  else assert(false);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}
