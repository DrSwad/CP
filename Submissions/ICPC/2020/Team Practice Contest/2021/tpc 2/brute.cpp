#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
const int N = 2005;
const int MAX_EXP = 50;

int n, m;
int g[N][N];

int emptyCellsInSquare(int r1, int c1, int r2, int c2) {
  int color = 0;
  int cnt = 0;

  for (int r = r1; r <= r2; r++) {
    for (int c = c1; c <= c2; c++) {
      if (color and g[r][c] and g[r][c] != color) return -1;
      if (g[r][c]) color = g[r][c];
      else cnt++;
    }
  }

  return cnt;
}

int main() {
  scanf("%d %d", &n, &m);

  vector<int> charIndex(max('R', '*') + 1);
  charIndex['*'] = 0;
  charIndex['R'] = 1;
  charIndex['G'] = 2;
  charIndex['B'] = 3;

  for (int r = 1; r <= n; r++) {
    for (int c = 1; c <= m; c++) {
      char ch;
      scanf(" %c", &ch);
      g[r][c] = charIndex[ch];
    }
  }

  vector<ld> inv3(MAX_EXP);
  inv3[0] = 1;
  for (int i = 1; i < MAX_EXP; i++) {
    inv3[i] = inv3[i - 1] / 3;
  }

  ld ans = 0;

  for (int r1 = 1; r1 <= n; r1++) {
    for (int c1 = 1; c1 <= m; c1++) {
      for (int d = 1; d <= n; d++) {
        int r2 = r1 + d - 1;
        int c2 = c1 + d - 1;
        if (r2 > n or c2 > m) break;
        int cnt = emptyCellsInSquare(r1, c1, r2, c2);
        if (cnt == -1 or cnt >= MAX_EXP) continue;
        int coeff = cnt == (r2 - r1 + 1) * (c2 - c1 + 1) ? 3 : 1;
        ans += coeff * inv3[cnt];
      }
    }
  }

  cout << fixed << setprecision(6) << ans << endl;
}