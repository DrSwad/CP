#include <bits/stdc++.h>
using namespace std;

const int N = 5000;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int m, n;
  cin >> m >> n;

  vector<int> p(n);
  for (int &i : p) cin >> i;

  vector r(m, vector(n, 0));
  for (auto &row : r) {
    for (int &j : row) {
      cin >> j;
    }
  }

  vector<bitset<N>> bs(n);
  for (int j = 0; j < n; j++) {
    bs[j].flip();
  }

  for (int i = 0; i < m; i++) {
    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    sort(
      order.begin(),
      order.end(),
      [&](int j1, int j2) {
      return r[i][j1] < r[i][j2];
    }
      );

    bitset<N> row_bs;
    for (int j = n - 1; j >= 0; j--) {
      if (j<n - 1 and r[i][order[j + 1]]> r[i][order[j]]) {
        int k = j + 1;
        while (k < n and r[i][order[k]] == r[i][order[j + 1]]) {
          row_bs[order[k++]] = 1;
        }
      }
      bs[order[j]] &= row_bs;
    }
  }

  vector<int> order(n);
  iota(order.begin(), order.end(), 0);
  sort(
    order.begin(),
    order.end(),
    [&](int j1, int j2) {
    return r[0][j1] < r[0][j2];
  }
    );

  vector<long long> dp(n);
  for (int oj = n - 1; oj >= 0; oj--) {
    int j = order[oj];
    dp[j] = p[j];
    for (int nj = 0; nj < n; nj++) {
      if (bs[j][nj]) {
        dp[j] = max(dp[j], dp[nj] + p[j]);
      }
    }
  }

  cout << *max_element(dp.begin(), dp.end()) << "\n";

  return 0;
}