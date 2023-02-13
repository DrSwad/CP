#include <bits/stdc++.h>
using namespace std;

const int N = 1000;

bitset<4 * N + 1> bs[2][N + 1];

void test_case() {
  int n, m;
  cin >> n >> m;

  vector<vector<int>> a(n, vector<int>(m));
  for (auto &row : a) {
    for (auto &i : row) {
      cin >> i;
    }
  }

  for (int i = 1; i <= n; i++) {
    bs[0][i] = 0;
  }
  bs[0][1][0] = 1;

  for (int j = 1; j <= m; j++) {
    int bi = j & 1;
    for (int i = 1; i <= n; i++) {
      if (a[i - 1][j - 1] == 1) {
        bs[bi][i] = bs[bi ^ 1][i] << 1 | bs[bi][i - 1] << 1;
      }
      else {
        bs[bi][i] = bs[bi ^ 1][i] >> 1 | bs[bi][i - 1] >> 1;
      }
    }
  }

  cout << (bs[m & 1][n][0] ? "YES\n" : "NO\n");
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