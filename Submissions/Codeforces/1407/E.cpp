#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector adj(2 * n, vector<int>());
  while (m--) {
    int from, to, type;
    cin >> from >> to >> type;
    from--, to--;

    if (from != to) {
      adj[2 * to].push_back(2 * from + type);
      adj[2 * to + 1].push_back(2 * from + type);
    }
  }

  vector vis(2 * n, false);
  vis[2 * n - 1] = vis[2 * n - 2] = true;

  vector dist(n, n);
  dist[n - 1] = 0;

  queue<int> q;
  q.push(n - 1);

  vector color(n, 0);

  while (!q.empty()) {
    int at = q.front();
    q.pop();

    for (int type = 0; type < 2; type++) {
      for (int to_cell : adj[2 * at + type]) {
        if (!vis[to_cell]) {
          vis[to_cell] = true;
          int to = to_cell / 2;
          if (vis[2 * to] and vis[2 * to + 1]) {
            dist[to] = dist[at] + 1;
            q.push(to);
          }
          else {
            color[to] = (to_cell & 1) ^ 1;
          }
        }
      }
    }
  }

  cout << (dist[0] == n ? -1 : dist[0]) << "\n";
  for (int i = 0; i < n; i++) {
    cout << color[i];
  }
  cout << "\n";

  return 0;
}