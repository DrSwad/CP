#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, m, r, c;
  cin >> n >> m >> r >> c;

  vector<string> g(n);
  for (auto &row : g) cin >> row;

  r--, c--;
  if (g[r][c] == 'B') cout << "0\n";
  else {
    bool has_black = false;
    for (auto row : g) {
      has_black = has_black or count(row.begin(), row.end(), 'B') >= 1;
    }

    if (!has_black) cout << "-1\n";
    else {
      bool row_or_col = false;
      for (auto row : g) {
        row_or_col = row_or_col or row[c] == 'B';
      }
      for (int i = 0; i < m; i++) {
        row_or_col = row_or_col or g[r][i] == 'B';
      }

      if (row_or_col) cout << "1\n";
      else cout << "2\n";
    }
  }
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