#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int rows, cols;
  cin >> rows >> cols;

  vector<string> grid(rows);
  for (string &row : grid) cin >> row;

  const string s = "snuke";

  vector vis(rows, vector(cols, false));
  const int dx[] = {0, +1, 0, -1};
  const int dy[] = {+1, 0, -1, 0};

  function<void(int, int, int)> dfs =
    [&](int at_row, int at_col, int at_char) {
      if (vis[at_row][at_col]) return;
      if (s[at_char] != grid[at_row][at_col]) return;
      vis[at_row][at_col] = true;
      for (int i = 0; i < 4; i++) {
        int to_row = at_row + dx[i];
        int to_col = at_col + dy[i];
        if (to_row < 0 or rows <= to_row) continue;
        if (to_col < 0 or cols <= to_col) continue;
        dfs(to_row, to_col, (at_char + 1) % 5);
      }
    };

  if (grid[0][0] != s[0]) cout << "No\n";
  else {
    dfs(0, 0, 0);
    if (vis[rows - 1][cols - 1]) cout << "Yes\n";
    else cout << "No\n";
  }

  return 0;
}