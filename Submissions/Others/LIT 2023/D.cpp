#include <bits/stdc++.h>
using namespace std;

const int dr[] = {+1, 0, -1, 0};
const int dc[] = {0, +1, 0, -1};

void test_case() {
  int n;
  cin >> n;

  bool parity_normal;
  vector ranges(n, vector(n, pair<int, int>(INT_MAX, INT_MAX)));
  queue<pair<int, int>> q;
  vector in_queue(n, vector(n, false));

  for (int r = 0; r < n; r++) {
    for (int c = 0; c < n; c++) {
      int val;
      cin >> val;
      if (val != 0) {
        parity_normal = val % 2 == (r + c) % 2;
        ranges[r][c] = {val / 2, val / 2};
        in_queue[r][c] = true;
        q.emplace(r, c);
      }
    }
  }

  while (!q.empty()) {
    auto [r, c] = q.front();
    q.pop();

    in_queue[r][c] = false;
    auto [L, R] = ranges[r][c];

    if (parity_normal == ((r + c) % 2 == 0)) L--;
    else R++;

    for (int dir = 0; dir < 4; dir++) {
      int nr = r + dr[dir];
      int nc = c + dc[dir];
      if (0 <= nr and nr < n and 0 <= nc and nc < n) {
        auto [pL, pR] = ranges[nr][nc];
        int nL, nR;
        if (pL == INT_MAX or pR == INT_MAX) nL = L, nR = R;
        else nL = max(L, pL), nR = min(R, pR);
        if (nL != pL or nR != pR) {
          ranges[nr][nc] = {nL, nR};
          if (!in_queue[nr][nc]) {
            q.emplace(nr, nc);
            in_queue[nr][nc] = true;
          }
        }
      }
    }
  }

  for (int r = 0; r < n; r++) {
    for (int c = 0; c < n; c++) {
      if (c) cout << " ";
      auto [L, R] = ranges[r][c];
      if (L != R) cout << "0";
      else cout << 2 * L + (parity_normal == (r + c) % 2 == 1);
    }
    cout << "\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}