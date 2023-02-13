#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, m;
  cin >> n >> m;

  vector<vector<int>> a(n, vector<int>(m));

  int mx = -1, px, py;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> a[i][j];
      if (a[i][j] > mx) {
        mx = a[i][j], px = i, py = j;
      }
    }
  }

  int X = max(px + 1, n - px);
  int Y = max(py + 1, m - py);
  cout << X * Y << "\n";
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