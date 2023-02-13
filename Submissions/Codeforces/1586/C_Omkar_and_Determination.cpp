#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, m;
  cin >> n >> m;

  vector<string> g(n + 1);
  g[0] = string(m + 1, ' ');
  for (int i = 1; i <= n; i++) {
    cin >> g[i];
    g[i] = " " + g[i];
  }

  vector<vector<int>> pref(n + 1, vector<int>(m + 1));
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= m; j++) {
      if (i == 0 or j == 0) {
        pref[i][j] = 0;
      }
      else {
        pref[i][j] = pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1];
        pref[i][j] += (g[i - 1][j] == 'X' and g[i][j - 1] == 'X');
      }
    }
  }

  int q;
  cin >> q;

  while (q--) {
    int j1, j2;
    cin >> j1 >> j2;

    if (pref[n][j2] - pref[n][j1]) cout << "NO\n";
    else cout << "YES\n";
  }

  return 0;
}