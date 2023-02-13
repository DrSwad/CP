#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, m;
  cin >> n >> m;

  vector<vector<int>> a(n, vector<int>(m));
  for (auto &row : a) {
    for (int &i : row) cin >> i;
  }

  auto check = [&](int sz) {
    vector<vector<int>> right(n, vector<int>(m));
    for (int i = n - 1; i >= 0; i--) {
      right[i][m - 1] = a[i][m - 1] >= sz;
      for (int j = m - 2; j >= 0; j--) {
        right[i][j] = a[i][j] < sz ? 0 : 1 + right[i][j + 1];
      }
    }

    vector<vector<int>> down(n, vector<int>(m));
    for (int j = m - 1; j >= 0; j--) {
      down[n - 1][j] = a[n - 1][j] >= sz;
      for (int i = n - 2; i >= 0; i--) {
        down[i][j] = a[i][j] < sz ? 0 : 1 + down[i + 1][j];
      }
    }

    vector<vector<int>> diagonal(n + 1, vector<int>(m + 1, 0));
    for (int i = n - 1; i >= 0; i--) {
      for (int j = m - 1; j >= 0; j--) {
        diagonal[i][j] = min(right[i][j], min(down[i][j], 1 + diagonal[i + 1][j + 1]));
        if (diagonal[i][j] >= sz) return true;
      }
    }

    return false;
  };

  int L = 1, R = min(n, m) + 1;
  while (R - L > 1) {
    int mid = (L + R) / 2;
    if (check(mid)) L = mid;
    else R = mid;
  }

  cout << L << "\n";
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