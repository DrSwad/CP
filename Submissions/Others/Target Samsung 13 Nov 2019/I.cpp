#include <bits/stdc++.h>
using namespace std;

const int N = 10;
const int M = 10;

int rows, cols;
int grid[N][M];
int start_row, start_col, end_row, end_col;

int max_height;
vector<pair<int, int>> edges[N][N];
bool vis[N][M];

void dfs(int at_row, int at_col) {
  if (vis[at_row][at_col]) return;
  vis[at_row][at_col] = true;

  for (auto [to_row, to_col] : edges[at_row][at_col]) {
    dfs(to_row, to_col);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> rows >> cols;
  start_row = rows - 1, start_col = 0;
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      cin >> grid[row][col];
      if (grid[row][col] == 3) {
        end_row = row, end_col = col;
      }
    }
  }

  for (max_height = 0; ; max_height++) {
    for (int row = 0; row < rows; row++) {
      for (int col = 0; col < cols; col++) {
        edges[row][col].clear();
        vis[row][col] = false;

        if (grid[row][col] == 0) continue;

        if (col + 1 < cols and grid[row][col + 1] != 0) {
          edges[row][col].emplace_back(row, col + 1);
        }
        if (col - 1 >= 0 and grid[row][col - 1] != 0) {
          edges[row][col].emplace_back(row, col - 1);
        }
        for (int height = 1; height <= max_height; height++) {
          if (row + height < rows and grid[row + height][col] != 0) {
            edges[row][col].emplace_back(row + height, col);
          }
          if (row - height >= 0 and grid[row - height][col] != 0) {
            edges[row][col].emplace_back(row - height, col);
          }
        }
      }
    }

    dfs(start_row, start_col);

    if (vis[end_row][end_col]) {
      cout << max_height << "\n";
      break;
    }
  }

  return 0;
}