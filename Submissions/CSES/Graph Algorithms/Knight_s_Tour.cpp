#include <bits/stdc++.h>
using namespace std;

const int D = 8;

int dx[] = {2, 2, -2, -2, 1, 1, -1, -1};
int dy[] = {1, -1, 1, -1, 2, -2, 2, -2};

int turn[D][D];
int rem = D * D;

int degree(int x, int y) {
  int ret = 0;
  for (int i = 0; i < 8; i++) {
    int nx = x + dx[i];
    int ny = y + dy[i];
    if (0 <= nx and nx < D and 0 <= ny and ny < D) { ret++; }
  }
  return ret;
}

bool backtrack(int x, int y, int px = 0, int py = 0, int t = 1) {
  if (turn[x][y]) { return false; }

  turn[x][y] = t;
  rem--;
  if (rem == 0) { return true; }

  vector<tuple<int, int, int>> nxt;
  for (int i = 0; i < 8; i++) {
    int nx = x + dx[i];
    int ny = y + dy[i];
    if (0 <= nx and nx < D and 0 <= ny and ny < D) {
      nxt.emplace_back(degree(nx, ny), nx, ny);
    }
  }

  sort(nxt.begin(), nxt.end());

  for (auto &to : nxt) {
    if (backtrack(get<1>(to), get<2>(to), x, y, t + 1)) {
      return true;
    }
  }

  turn[x][y] = 0;
  rem++;

  return false;
}

int main() {
  int x, y;
  cin >> y >> x;
  x--, y--;

  backtrack(x, y);

  for (int i = 0; i < D; i++) {
    for (int j = 0; j < D; j++) {
      if (j) { printf(" "); }
      printf("%d", turn[i][j]);
    }
    puts("");
  }

  return 0;
}