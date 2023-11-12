#include <bits/stdc++.h>

using namespace std;

const int N = 69;

int dx[] = { 0, +1,  0, -1};
int dy[] = {-1,  0, +1,  0};

inline int getDir(char c) {
  if (c == 'N') return 0;
  if (c == 'E') return 1;
  if (c == 'S') return 2;
  if (c == 'W') return 3;
  assert(false);
}

int n, m, src_x, src_y, snk_x, snk_y, d[N][N][N], g[N][N];
int ans = INT_MAX;
int max_moves = 20;

void go(int at_x, int at_y, int moves) {
  if (at_x == snk_x and at_y == snk_y) {
    ans = min(ans, moves);
    return;
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> m;
  cin >> src_x >> src_y;
  cin >> snk_x >> snk_y;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      string moves; cin >> moves;
      if (moves[0] == 'x') continue;
      for (char c : moves) g[i][j] |= 1 << getDir(c);
    }
  }
  memset(d, 63, sizeof d);
  queue<array<int, 3>> Q;
  Q.push({src_x, src_y, 1});
  d[src_x][src_y][1] = 0;
  int ans = INT_MAX;
  while (!Q.empty()) {
    auto [x, y, rem] = Q.front(); Q.pop();
    if (x == snk_x and y == snk_y) {
      ans = min(ans, d[x][y][rem]);
      continue;
    }
    if (rem + 1 < N and d[x][y][rem + 1] > 1 + d[x][y][rem]) {
      d[x][y][rem + 1] = 1 + d[x][y][rem];
      Q.push({x, y, rem + 1});
    }
    for (int sgn : {-1, 1}) {
      for (int rot = 0; rot < 4; ++rot) if (rot <= rem) {
          for (int i = 0; i < 4; ++i) if (g[x][y] & 1 << i) {
              int dir = (i + 4 + rot * sgn) & 3, new_x = x + dx[dir], new_y = y + dy[dir];
              if (d[new_x][new_y][rem - rot + 1] > 1 + d[x][y][rem]) {
                d[new_x][new_y][rem - rot + 1] = 1 + d[x][y][rem];
                Q.push({new_x, new_y, rem - rot + 1});
              }
            }
        }
    }
  }
  cout << ans << '\n';
  return 0;
}
