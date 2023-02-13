#include <bits/stdc++.h>

using namespace std;
const int N = 20;

int mat[N][N];

vector<int> ans, value;
int profit = -1;
int n;

void call(int i, int s) {

  if (s == 0) {
    int cur_profit = 0;
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        cur_profit += min(value[i], value[j]) * mat[i][j];
      }
    }

    // for (int i = 0; i < n; i++) {
    //   cout << value[i] << " \n"[i == n - 1];
    // }

    // cout << cur_profit << endl;

    if (cur_profit > profit) {
      ans = value;
      profit = cur_profit;
    }
    return;
  }

  if (i == n) return;

  for (int r = s; r >= 0; r--) {
    value[i] = r;
    call(i + 1, s - r);
    value[i] = 0;
  }
}

int main() {

  int m, s, u, v;
  cin >> n >> m >> s;
  for (int i = 0; i < m; i++) {
    cin >> u >> v;
    u--, v--;
    if (u > v) swap(u, v);
    mat[u][v]++;
  }

  value.resize(n);
  call(0, s);

  for (int i = 0; i < n; i++) {
    cout << ans[i] << " \n"[i == n - 1];
  }

  return 0;
}