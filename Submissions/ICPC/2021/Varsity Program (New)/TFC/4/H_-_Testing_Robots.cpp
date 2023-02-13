#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int X, Y;
  cin >> X >> Y;

  int x, y;
  cin >> x >> y;
  x--, y--;

  string s;
  cin >> s;

  int tot = 0;
  int n = s.length();
  vector<vector<bool>> vis(X, vector<bool>(Y, false));

  cout << "1";
  tot++;
  vis[x][y] = true;

  for (int i = 0; i < n - 1; i++) {
    int nx = x, ny = y;
    if (s[i] == 'U') nx = max(0, nx - 1);
    if (s[i] == 'D') nx = min(X - 1, nx + 1);
    if (s[i] == 'L') ny = max(0, ny - 1);
    if (s[i] == 'R') ny = min(Y - 1, ny + 1);
    if (vis[nx][ny]) cout << " 0";
    else cout << " 1", tot++;
    vis[nx][ny] = true;
    x = nx, y = ny;
  }

  cout << " " << X * Y - tot << "\n";

  return 0;
}