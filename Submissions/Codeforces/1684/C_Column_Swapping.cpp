#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, m;
  cin >> n >> m;

  vector<vector<int>> a(n, vector<int>(m));
  for (auto &row : a) {
    for (auto &cell : row) {
      cin >> cell;
    }
  }

  bool possible = true;
  int l = -1, r = -1;

  for (int i = 0; i < n; i++) {
    for (int j = 0, pi = -1, pv = 0; j < m - 1; j++) {
      if (a[i][j] != pv) {
        pi = j;
        pv = a[i][j];
      }
      if (a[i][j + 1] < a[i][j]) {
        if (l != -1 and l != pi) possible = false;
        l = pi;
        break;
      }
    }
    for (int j = m - 1, pi = -1, pv = 0; j > 0; j--) {
      if (a[i][j] != pv) {
        pi = j;
        pv = a[i][j];
      }
      if (a[i][j - 1] > a[i][j]) {
        if (r != -1 and r != pi) possible = false;
        r = pi;
        break;
      }
    }
  }

  if (!possible) cout << "-1\n";
  else {
    if (l == -1 or r == -1) {
      assert(l == -1 and r == -1);
      l = r = 0;
    }

    for (int i = 0; i < n; i++) {
      swap(a[i][l], a[i][r]);
      possible = possible and is_sorted(a[i].begin(), a[i].end());
    }

    if (!possible) cout << "-1\n";
    else cout << l + 1 << " " << r + 1 << "\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}