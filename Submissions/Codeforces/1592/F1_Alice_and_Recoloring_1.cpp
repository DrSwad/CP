#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, m;
  cin >> n >> m;

  vector<vector<int>> a(n + 1, vector<int>(m + 1, 0));
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    for (int j = 0; j < m; j++) {
      a[i][j] = s[j] == 'B';
    }
  }

  vector<vector<int>> b(n, vector<int>(m));
  int ans = 0;
  bool rect = false;

  for (int i = n - 1; i >= 0; i--) {
    for (int j = m - 1; j >= 0; j--) {
      b[i][j] = (a[i][j] + a[i][j + 1] + a[i + 1][j] + a[i + 1][j + 1]) % 2;
      ans += b[i][j];
      if (i < n - 1 and j < m - 1) {
        rect = rect or (b[i][j] and b[i][m - 1] and b[n - 1][j] and b[n - 1][m - 1]);
      }
    }
  }

  cout << (ans - rect) << "\n";

  return 0;
}