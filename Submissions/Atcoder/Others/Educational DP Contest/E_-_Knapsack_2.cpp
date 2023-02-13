// https://atcoder.jp/contests/dp/tasks/dp_e

#include <bits/stdc++.h>
#define ll long long int
using namespace std;
const int N = 105;
const int V = 100005;
const ll INF = 1e12;
ll wt[N], val[N];
ll dp[N][V];
ll solve(int ind, int val_left) {
  if (val_left == 0) return 0;
  if (ind < 0) return INF;
  if (dp[ind][val_left] != -1) return dp[ind][val_left];
  ll ans = solve(ind - 1, val_left);

  if (val_left - val[ind] >= 0) {
    ans = min(ans, solve(ind - 1, val_left - val[ind]) + wt[ind]);
  }

  return dp[ind][val_left] = ans;
}

int main() {
  memset(dp, -1, sizeof dp);

  int n, w;
  cin >> n >> w;
  for (int i = 0; i < n; i++) {
    cin >> wt[i] >> val[i];
  }
  for (int i = V - 1; i >= 0; i--) {
    if (solve(n - 1, i) <= w) {
      cout << i << endl;
      break;
    }
  }

  return 0;
}