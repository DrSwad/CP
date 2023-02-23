#include <bits/stdc++.h>
using namespace std;

int main() {
  int rows = 50, cols = 50;

  vector<string> grid(rows, string(cols, 'a'));
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      grid[row][col] = (row + col) % 26 + 'A';
    }
  }

  grid[rows - 1][cols - 1] = '*';

  string q;
  for (int i = 0; i < int(1e4); i++) {
    q += i % 26 + 'A';
  }

  cout << rows << " " << cols << "\n";
  for (auto &row : grid) cout << row << "\n";
  cout << q << "\n";

  return 0;
}