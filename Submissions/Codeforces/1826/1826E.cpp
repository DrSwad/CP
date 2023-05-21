#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int m, n;
  cin >> m >> n;

  vector<int> p(n);
  for (int &i : p) cin >> i;

  vector r(n, vector(m, 0));
  for (int j = 0; j < m; j++) {
    for (int i = 0; i < n; i++) {
      cin >> r[i][j];
    }
  }

  vector<int> order(n);
  iota(order.begin(), order.end(), 0);
  sort(
    order.begin(),
    order.end(),
    [&](int i, int j) {
    return r[i][0] < r[j][0];
  }
    );

  vector<long long> dp(n);
  for (int i = 0; i < n; i++) {
    dp[i] = p[order[i]];

    for (int pi = 0; pi < i; pi++) {
      bool flag = true;
      for (int j = 0; j < m and flag; j++) {
        flag = flag and r[order[pi]][j] < r[order[i]][j];
      }

      if (flag) dp[i] = max(dp[i], dp[pi] + p[order[i]]);
    }
  }

  cout << *max_element(dp.begin(), dp.end()) << "\n";

  return 0;
}