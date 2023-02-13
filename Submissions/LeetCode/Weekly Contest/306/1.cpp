#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  vector<vector<int>> largestLocal(vector<vector<int>> grid) {
    int n = grid.size();
    vector<vector<int>> ret(n - 2, vector<int>(n - 2));
    for (int i = 1; i < n - 1; i++) {
      for (int j = 1; j < n - 1; j++) {
        int mx = 0;
        for (int ni = i - 1; ni <= i + 1; ni++) {
          for (int nj = j - 1; nj <= j + 1; nj++) {
            mx = max(mx, grid[ni][nj]);
          }
        }
        ret[i - 1][j - 1] = mx;
      }
    }
    return ret;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  debug(Solution().largestLocal({{1, 1, 1, 1, 1}, {1, 1, 1, 1, 1}, {1, 1, 2, 1, 1}, {1, 1, 1, 1, 1}, {1, 1, 1, 1, 1}}));

  return 0;
}