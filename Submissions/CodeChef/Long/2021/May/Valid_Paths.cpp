#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int MOD = 1e9 + 7;

int n;
vector<int> e[N];
long long dp[N];

int dfs(int at, int from = 0) {
  if (at != 1 and e[at].size() == 1) {
    dp[at] = 1;
    return 1;
  }

  long long ret = 1;
  dp[at] = 1;

  for (int to : e[at]) {
    if (to != from) {
      ret += dfs(to, at);
      ret += dp[at] * dp[to];
      ret %= MOD;
      dp[at] += dp[to] << 1;
    }
  }
  dp[at] %= MOD;

  return ret;
}

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    scanf("%d", &n);

    for (int i = 1; i < n; i++) {
      int u, v;
      scanf("%d %d", &u, &v);
      e[u].push_back(v);
      e[v].push_back(u);
    }

    printf("%d\n", dfs(1));

    for (int i = 1; i <= n; i++) e[i].clear();
  }

  return 0;
}