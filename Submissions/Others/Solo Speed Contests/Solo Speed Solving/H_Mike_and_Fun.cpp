#include <bits/stdc++.h>
using namespace std;

const int N = 505;

int n, m, q;
int g[N][N];
int row_max[N];

void calcRowMax(int i) {
  row_max[i] = 0;

  for (int j = 1, curr = 0; j <= m; j++) {
    if (g[i][j]) curr++;
    else curr = 0;
    row_max[i] = max(row_max[i], curr);
  }
}

int main() {
  cin >> n >> m >> q;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      scanf("%d", &g[i][j]);
    }
  }

  for (int i = 1; i <= n; i++) calcRowMax(i);

  for (int qq = 1; qq <= q; qq++) {
    int i, j;
    scanf("%d %d", &i, &j);
    g[i][j] = !g[i][j];

    calcRowMax(i);

    int ans = *max_element(row_max + 1, row_max + n + 1);
    printf("%d\n", ans);
  }

  return 0;
}