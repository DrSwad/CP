#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int n;
vector<int> e[N];
int min_days[N];
vector<int> assassins_at[N];

void reset() {
  for (int i = 1; i <= n; i++) {
    e[i].clear();
    min_days[i] = 0;
  }
  assassins_at[1].clear();
}

void init_dfs(int at, int from = 0) {
  int mini = n, freq = 0;
  int children = 0;

  for (int to : e[at]) {
    if (to != from) {
      children++;
      init_dfs(to, at);

      if (min_days[to] + 1 <= mini) {
        freq = min_days[to] + 1 == mini ? freq + 1 : 1;
        mini = min_days[to] + 1;
      }
    }
  }

  if (at == 1) min_days[at] = mini;
  else if (!children) min_days[at] = 0;
  else min_days[at] = freq == children ? mini : mini + 1;
}

void solve_dfs(int at, int from = 0, int merge_day = n) {
  vector<int> alive;
  int children = 0;
  for (int to : e[at]) {
    if (to != from) {
      children++;
      if ((at == 1 and min_days[to] + 1 == min_days[at]) or (at != 1 and (min_days[to] + 1 >= merge_day or min_days[to] + 1 >= min_days[at])))
      {
        alive.push_back(to);
        solve_dfs(to, at, min(merge_day, at == 1 ? n : min_days[at]));
      }
    }
  }

  if (!children) {
    assassins_at[at].push_back(at);
    return;
  }

  int max_at = -1;
  for (int to : alive) {
    if (max_at == -1 or assassins_at[to].size() > assassins_at[max_at].size()) {
      max_at = to;
    }
  }

  for (int to : alive) {
    if (to != max_at) {
      vector<int> &fromv = assassins_at[to];
      vector<int> &tov = assassins_at[max_at];
      for (int i : fromv) tov.push_back(i);
      fromv.clear();
    }
  }

  if (~max_at) swap(assassins_at[at], assassins_at[max_at]);
}

vector<int> solve() {
  init_dfs(1);
  solve_dfs(1);
  return assassins_at[1];
}

int main() {
  int t;
  cin >> t;

  while (t--) {
    scanf("%d", &n);

    for (int i = 1; i < n; i++) {
      int u, v;
      scanf("%d %d", &u, &v);
      e[u].push_back(v);
      e[v].push_back(u);
    }

    vector<int> ans = solve();
    sort(ans.begin(), ans.end());
    printf("%d %d\n", ans.size(), min_days[1]);
    for (int i = 0; i < ans.size(); i++) {
      if (i) printf(" ");
      printf("%d", ans[i]);
    }
    puts("");

    reset();
  }

  return 0;
}