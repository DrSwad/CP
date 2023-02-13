#include <bits/stdc++.h>
using namespace std;

const int N = 20;
const int K = 5;

int k, rows, cols;
int g[N][N];
pair<int, int> sos[K];
int dist[K][N][N];
int dr[] = {+1, -1, 0, 0};
int dc[] = {0, 0, +1, -1};

void go(int id) {
  dist[id][sos[id].first][sos[id].second] = 0;
  queue<pair<int, int>> que;
  que.push(sos[id]);

  while (!que.empty()) {
    auto [r, c] = que.front();
    que.pop();
    for (int i = 0; i < 4; i++) {
      int nr = r + dr[i];
      int nc = c + dc[i];
      if (~nr and nr < rows and ~nc and nc < cols) {
        if (dist[id][nr][nc] == -1
            or dist[id][nr][nc] > dist[id][r][c] + 1) {
          dist[id][nr][nc] = dist[id][r][c] + 1;
          if (g[nr][nc] == 1) que.push({nr, nc});
        }
      }
    }
  }
}

int main() {
  memset(dist, -1, sizeof dist);

  while (cin >> k >> rows >> cols) {
    for (int r = 0; r < rows; r++) {
      for (int c = 0; c < cols; c++) { scanf("%d", &g[r][c]); }
    }

    for (int i = 0; i < k; i++) {
      scanf("%d %d", &sos[i].first, &sos[i].second);
      go(i);
    }

    int ans = -1;
    for (int r = 0; r < rows; r++) {
      for (int c = 0; c < cols; c++) {
        if (g[r][c] == 0) {
          int curr = 0;
          for (int id = 0; id < k; id++) {
            if (curr != -1) {
              if (dist[id][r][c] != -1) {
                curr = max(curr, dist[id][r][c]);
              } else {
                curr = -1;
              }
            }
          }
          if (curr != -1) ans = ans == -1 ? curr : min(ans, curr);
        }
        for (int id = 0; id < k; id++) { dist[id][r][c] = -1; }
      }
    }
    printf("%d\n", ans);
  }

  return 0;
}