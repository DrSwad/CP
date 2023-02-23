#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
const i64 INF = 1e18;

int dRow[] = {-1, -1, -1, 0, 0, +1, +1, +1};
int dCol[] = {-1, 0, +1, -1, +1, -1, 0, +1};

void test_case() {
  int n, m, p, q;
  scanf("%d%d%d%d", &n, &m, &p, &q);

  int Sx, Sy, Dx, Dy;
  scanf("%d%d%d%d", &Sx, &Sy, &Dx, &Dy);

  vector<int> C(8);
  for (int&i : C) scanf("%d", &i);

  vector<array<int, 3>> G[n + 2][m + 2];

  for (int i = 0; i < p; i++) {
    int Ux, Uy, Vx, Vy, W;
    scanf("%d%d%d%d%d", &Ux, &Uy, &Vx, &Vy, &W);
    G[Ux][Uy].push_back({Vx, Vy, W});
  }

  int vis[n + 2][m + 2][8];
  memset(vis, 0, sizeof vis);

  for (int i = 0; i < q; i++) {
    int x, y;
    scanf("%d%d", &x, &y);

    for (int j = 0; j < 8; j++) {
      vis[x][y][j] = 1;
    }
  }

  i64 dist[n + 2][m + 2][8];
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      for (int k = 0; k < 8; k++) {
        dist[i][j][k] = INF;
      }
    }
  }
  for (int i = 0; i < 8; i++) {
    dist[Sx][Sy][i] = 0;
    vis[Sx][Sy][i] = 1;
  }

  priority_queue<array<i64, 3>> PQ;
  PQ.push({0, Sx, Sy});

  auto is_valid = [&](int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= m;
  };

  int vis2[n + 2][m + 2];
  memset(vis2, 0, sizeof vis2);

  while (!PQ.empty()) {
    auto [w, x, y] = PQ.top(); PQ.pop();
    w = -w;

    if (vis2[x][y]) continue;
    vis2[x][y] = true;

    for (int dir = 0; dir < 8; dir++) {
      for (int k = 1; ; k++) {
        int nX = x + dRow[dir] * k;
        int nY = y + dCol[dir] * k;

        if (!is_valid(nX, nY)) {
          break;
        }

        if (vis[nX][nY][dir]) break;

        if (dist[nX][nY][dir] > w + C[dir]) {
          dist[nX][nY][dir] = w + C[dir];
          vis[nX][nY][dir] = 1;
          PQ.push({-(w + C[dir]), nX, nY});
        }
      }
    }

    for (auto it : G[x][y]) {
      int nX = it[0];
      int nY = it[1];

      for (int dir = 0; dir < 8; dir++) {
        if (dist[nX][nY][dir] > w + it[2]) {
          dist[nX][nY][dir] = w + it[2];
          PQ.push({-(w + it[2]), nX, nY});
        }
      }
    }
  }

  i64 ans = INF;
  for (int i = 0; i < 8; i++) {
    ans = min(ans, dist[Dx][Dy][i]);
  }

  if (ans == INF) ans = -1;

  printf("%lld\n", ans);
}

int main() {
  int t;
  scanf("%d", &t);

  for (int cs = 1; cs <= t; cs++) {
    printf("Case %d: ", cs);
    test_case();
  }

  return 0;
}
