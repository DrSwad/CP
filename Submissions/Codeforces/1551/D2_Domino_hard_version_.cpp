#include <bits/stdc++.h>
using namespace std;

const int N = 105;

char color(int dir, int r, int c) {
  if (dir == 0) return 'a' + dir + (r % 2) * 2 + (c / 2 % 2) * 4;
  else return 'a' + dir + (c % 2) * 2 + (r / 2 % 2) * 4;
}

vector<vector<char>> construct(int R, int C, int H, int V) {
  vector<vector<char>> ans(R, vector<char>(C));

  for (int r = 0; r < R; r += 2) {
    for (int c = 0; c < C - 1; c += 2) {
      if (H) {
        ans[r][c] = ans[r][c + 1] = color(0, r, c);
        ans[r + 1][c] = ans[r + 1][c + 1] = color(0, r + 1, c);
        H -= 2;
      }
      else {
        ans[r][c] = ans[r + 1][c] = color(1, r, c);
        ans[r][c + 1] = ans[r + 1][c + 1] = color(1, r, c + 1);
      }
    }
  }

  if (C % 2 == 1) {
    for (int r = 0; r < R; r += 2) {
      ans[r][C - 1] = ans[r + 1][C - 1] = color(1, r, C - 1);
    }
  }

  return ans;
}

void test_case() {
  int R, C, H, V;
  cin >> R >> C >> H;
  V = R * C / 2 - H;

  if (R % 2 == 0) {
    if (H % 2 == 1 or H > R * (C / 2)) {
      cout << "NO\n";
      return;
    }
  }
  if (C % 2 == 0) {
    if (V % 2 == 1 or V > C * (R / 2)) {
      cout << "NO\n";
      return;
    }
  }

  vector<vector<char>> ans;
  if (R % 2 == 0) ans = construct(R, C, H, V);
  else {
    auto tans = construct(C, R, V, H);
    ans.resize(R, vector<char>(C));
    for (int i = 0; i < R; i++) {
      for (int j = 0; j < C; j++) {
        ans[i][j] = tans[j][i];
      }
    }
  }

  cout << "YES\n";
  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      cout << ans[i][j];
    }
    cout << "\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}