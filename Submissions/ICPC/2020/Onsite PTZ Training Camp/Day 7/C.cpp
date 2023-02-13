#include <bits/stdc++.h>
using namespace std;

const int N = 13;
const int C = 26;

vector<vector<int>> grid(N, vector<int>(N));
bool vis[26][26];

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void go(int row = 0, int col = 0) {
  if (col == N) col = 0, row++;
  if (row == N) {
    cout << N << "\n";
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        cout << (char)('a' + grid[i][j]);
      }
      cout << "\n";
    }

    exit(EXIT_SUCCESS);
  }

  vector<int> available;
  int c2 = -1, c3 = -1;
  for (int c = 0; c < C; c++) {
    if (row > 0) {
      c2 = grid[row - 1][col];
      if (vis[c2][c]) continue;
    }
    if (col > 0) {
      c3 = grid[row][col - 1];
      if (vis[c3][c]) continue;
    }
    available.push_back(c);
  }

  shuffle(available.begin(), available.end(), rng);

  for (int c : available) {
    if (c2 != -1) vis[c2][c] = true;
    if (c3 != -1) vis[c3][c] = true;
    grid[row][col] = c;
    go(row, col + 1);
    if (c2 != -1) vis[c2][c] = false;
    if (c3 != -1) vis[c3][c] = false;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  go();

  return 0;
}