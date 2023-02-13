#include <bits/stdc++.h>
using namespace std;

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

void test_case() {
  int n, m;
  cin >> n >> m;

  vector<vector<int>> a(n, vector<int>(m));
  for (auto &i : a) for (auto &j : i) cin >> j;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int cnt = 0;
      for (int d = 0; d < 4; d++) {
        int ii = i + dx[d];
        int jj = j + dy[d];
        cnt += ii >= 0 and jj >= 0 and ii < n and jj < m;
      }
      if (a[i][j] > cnt) {
        cout << "NO\n";
        return;
      }
      a[i][j] = cnt;
    }
  }

  cout << "YES\n";
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (j) cout << " ";
      cout << a[i][j];
    }
    cout << "\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}