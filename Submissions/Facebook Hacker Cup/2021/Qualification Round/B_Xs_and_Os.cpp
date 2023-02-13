#include <bits/stdc++.h>
using namespace std;

const int N = 55;

int n;
char g[N][N];
int pref[N][N];

int rect(int x1, int y1, int x2, int y2) {
  return pref[x2][y2] - pref[x1 - 1][y2] - pref[x2][y1 - 1] + pref[x1 - 1][y1 - 1];
}

int need(bool is_row, int id) {
  int freq = is_row ? rect(id, 1, id, n) : rect(1, id, n, id);
  return freq >= n ? -1 : n - freq;
}

void test_case() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf(" %s", g[i] + 1);
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      int curr = g[i][j] == 'X' ? 1 : g[i][j] == 'O' ? n : 0;
      pref[i][j] = curr + pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1];
    }
  }

  int mn = -1;
  for (int i = 1; i <= n; i++) {
    for (int is_row = 0; is_row < 2; is_row++) {
      int curr = need(is_row, i);
      if (curr != -1) {
        mn = mn == -1 ? curr : min(mn, curr);
      }
    }
  }

  if (mn == -1) {
    puts("Impossible");
    return;
  }

  int ans = 0;
  if (mn != 1) {
    for (int i = 1; i <= n; i++) {
      for (int is_row = 0; is_row < 2; is_row++) {
        ans += need(is_row, i) == mn;
      }
    }
  } else {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        if (g[i][j] == '.') {
          ans += need(true, i) == mn or need(false, j) == mn;
        }
      }
    }
  }

  printf("%d %d\n", mn, ans);
}

int main() {
  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    printf("Case #%d: ", cs);
    test_case();
  }

  return 0;
}