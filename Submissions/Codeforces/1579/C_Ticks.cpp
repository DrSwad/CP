#include <bits/stdc++.h>
using namespace std;

const int N = 25;

int n, m, k;
char g[N][N];

bool check(int x, int y, int d) {
  if (x <= d or y <= d or y + d > m) return false;
  for (int i = 0; i <= d; i++) {
    if (g[x - i][y - i] == '.') return false;
    if (g[x - i][y + i] == '.') return false;
  }
  return true;
}

void tick(int x, int y, int d) {
  for (int i = 0; i <= d; i++) {
    g[x - i][y - i] = '#';
    g[x - i][y + i] = '#';
  }
}

void test_case() {
  cin >> n >> m >> k;

  for (int i = 1; i <= n; i++) {
    cin >> (g[i] + 1);
  }

  for (int d = k; d <= min(n, m); d++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        if (check(i, j, d)) tick(i, j, d);
      }
    }
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (g[i][j] == '*') {
        cout << "NO\n";
        return;
      }
    }
  }

  cout << "YES\n";
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