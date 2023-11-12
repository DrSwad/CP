#include <iostream>
#include <vector>
using namespace std;

void test_case() {
  int rows, cols;
  cin >> rows >> cols;

  string need = "vika";
  int at_need = 0;

  vector<string> grid(rows);
  for (auto &row : grid) cin >> row;

  for (int col = 0; col < cols; col++) {
    for (int row = 0; row < rows; row++) {
      if (at_need < need.size() and grid[row][col] == need[at_need]) {
        at_need++;
        break;
      }
    }
  }

  if (at_need < need.size()) cout << "NO\n";
  else cout << "YES\n";
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