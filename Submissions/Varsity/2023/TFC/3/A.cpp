#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<vector<char>> grid(n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      char c;
      cin >> c;
      grid[i].push_back(c);
    }
  }

  int ans = 0;
  vector<bool> vis(n, false);
  for (int i = 0; i < n; i++) {
    if (vis[i]) continue;
    vector<int> got{i};

    queue<int> q;
    for (int j = 0; j < n; j++) {
      if (grid[i][j] == 'T') {
        q.push(j);
      }
    }

    bool okay = true;
    while (!q.empty()) {
      int ii = q.front(); q.pop();
      if (ii == i) continue;
      bool cur_okay = true;
      for (int j = 0; j < n; j++) {
        if (grid[i][j] != grid[ii][j]) {
          okay = cur_okay = false;
        }
      }
      if (!cur_okay) break;
      got.push_back(ii);
    }

    for (int ii : got) vis[ii] = true;
    if (okay) ans = max(ans, (int)got.size());
  }

  cout << ans << "\n";

  return 0;
}