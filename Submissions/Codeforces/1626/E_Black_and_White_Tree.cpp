#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 5;

int n;
int c[N];
vector<int> e[N];

int sub_black[N];
int sub_dp[N];
int ans[N];

void dfs1(int at, int from = 0) {
  sub_black[at] += c[at];
  sub_dp[at] = sub_dp[at] or c[at];

  for (int to : e[at]) {
    if (to != from) {
      dfs1(to, at);

      sub_dp[at] = sub_dp[at] or c[to];
      if (sub_black[to] >= 2) {
        sub_dp[at] = sub_dp[at] or sub_dp[to];
      }

      sub_black[at] += sub_black[to];
    }
  }

}

void dfs2(int at, int from = 0) {
  ans[at] = ans[at] or sub_dp[at];
  if (from != 0) {
    ans[at] = ans[at] or c[from];
  }

  int parent_black = sub_black[1] - sub_black[at];
  if (parent_black >= 2) {
    ans[at] = ans[at] or sub_dp[from];
  }

  for (int to : e[at]) {
    if (to != from) {
      dfs2(to, at);
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  for (int i = 1; i <= n; i++) cin >> c[i];
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    e[u].push_back(v);
    e[v].push_back(u);
  }

  dfs1(1);
  dfs2(1);

  for (int i = 1; i <= n; i++) {
    if (i > 1) cout << " ";
    cout << ans[i];
  }
  cout << "\n";

  return 0;
}