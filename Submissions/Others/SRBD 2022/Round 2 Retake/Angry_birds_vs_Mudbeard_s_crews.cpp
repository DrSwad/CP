#include <bits/stdc++.h>
using namespace std;

int dx[] = {0, -1, 0, 1};
int dy[] = {-1, 0, 1, 0};

void test_case() {
  int n, m;
  cin >> n >> m;

  vector<string> grid(n);
  for (string &row : grid) cin >> row;

  function<bool(int, int)> valid = [&](int i, int j) {
    return 0 <= i and i < n and 0 <= j and j < m;
  };

  vector<vector<bool>> open(n, vector<bool>(m, true));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (grid[i][j] == 'c') {
        open[i][j] = false;
        for (int d = 0; d < 4; d++) {
          int ni = i + dx[d];
          int nj = j + dy[d];
          if (valid(ni, nj)) open[ni][nj] = false;
        }
      }
    }
  }

  int bird_found = 0;
  vector<vector<bool>> vis(n, vector<bool>(m, false));

  function<void(int, int)> dfs = [&](int i, int j) {
    if (vis[i][j] or !open[i][j] or grid[i][j] == '#') return;
    vis[i][j] = true;
    if (grid[i][j] == 'b') bird_found++;
    for (int d = 0; d < 4; d++) {
      int ni = i + dx[d];
      int nj = j + dy[d];
      if (valid(ni, nj)) dfs(ni, nj);
    }
  };

  int tx, ty;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (grid[i][j] == 't') {
        tx = i, ty = j;
      }
    }
  }
  dfs(tx, ty);

  int tot_birds = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      tot_birds += grid[i][j] == 'b';
    }
  }

  cout << (bird_found == tot_birds ? "yes" : "no") << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}