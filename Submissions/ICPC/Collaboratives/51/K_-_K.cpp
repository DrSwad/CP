#include <bits/stdc++.h>
using namespace std;

const int N = 205;

int n;
string s[N];
bool is_row_pal[N][N][N];
bool is_col_pal[N][N][N];

bool is_sub_ok(int len, int x, int y) {
  if (len == 0 or len == 1) return true;
  for (int i = x; i < x + len; i++) {
    if (!is_row_pal[i][y][y + len - 1]) return false;
  }
  for (int j = y; j < y + len; j++) {
    if (!is_col_pal[j][x][x + len - 1]) return false;
  }
  return true;
}

bool check(int len) {
  for (int i = 0; i + len <= n; i++) {
    for (int j = 0; j + len <= n; j++) {
      if (is_sub_ok(len, i, j)) return true;
    }
  }
  return false;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  for (int i = 0; i < n; i++) cin >> s[i];

  for (int i = 0; i < n; i++) {
    for (int l = n - 1; l >= 0; l--) {
      for (int r = l; r < n; r++) {
        is_row_pal[i][l][r] = s[i][l] == s[i][r] and (l + 1 > r - 1 or is_row_pal[i][l + 1][r - 1]);
      }
    }
  }

  for (int j = 0; j < n; j++) {
    for (int l = n - 1; l >= 0; l--) {
      for (int r = l; r < n; r++) {
        is_col_pal[j][l][r] = s[l][j] == s[r][j] and (l + 1 > r - 1 or is_col_pal[j][l + 1][r - 1]);
      }
    }
  }

  int ans = 0;

  int L = 0, R = (n - 1) / 2 + 1;
  while (R > L + 1) {
    int mid = (R + L) / 2;
    if (check(2 * mid + 1)) L = mid;
    else R = mid;
  }

  ans = max(ans, 2 * L + 1);

  L = 0, R = n / 2 + 1;
  while (R > L + 1) {
    int mid = (R + L) / 2;
    if (check(2 * mid)) L = mid;
    else R = mid;
  }

  ans = max(ans, 2 * L);

  cout << ans << "\n";

  return 0;
}