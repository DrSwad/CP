#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int n;
vector<int> e[N];
int color[N];
int tot_leaf;
int rem;

void reset() {
  for (int i = 1; i <= n; i++) {
    e[i].clear();
    color[i] = 0;
  }
  tot_leaf = 0;
  rem = 0;
}

void dfs(int at, int from) {
  int tot_child = 0;
  for (int to : e[at]) {
    if (to != from) {
      tot_child++;
      dfs(to, at);
    }
  }

  if (!tot_child) tot_leaf++, color[at] = 1;
  else {
    color[at] = 1;
    int zero_cnt = 0;

    for (int to : e[at]) {
      if (to != from) {
        if (color[to] == 1) color[at] = 0;
        else zero_cnt++;
      }
    }

    rem += zero_cnt;
    if (tot_child == zero_cnt) rem--;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t;
  cin >> t;

  while (t--) {
    cin >> n;
    for (int i = 1; i < n; i++) {
      int u, v;
      cin >> u >> v;
      e[u].push_back(v);
      e[v].push_back(u);
    }

    dfs(1, 0);

    int ans = tot_leaf - rem;
    cout << ans << "\n";

    reset();
  }

  return 0;
}