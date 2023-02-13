#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> e;
vector<int> p;
vector<vector<int>> assassins_at, next_state;

void dfs(int at, int from = -1) {
  p[at] = from;
  for (int to : e[at]) if (to != from) dfs(to, at);
}

int topBlock(int from) {
  if (p[from] == -1) return -1;
  int ret = topBlock(p[from]);
  if (~ret) return ret;
  else if (assassins_at[p[from]].size()) {
    assert(p[from] != 0);
    return p[from];
  }
  else return -1;
}

bool isSafe(int at) {
  for (int to : e[at]) {
    if (to != p[at]) {
      if (assassins_at[to].size() or !isSafe(to)) return false;
    }
  }
  return true;
}

void moveAssassins(int at) {
  if (!isSafe(at)) return;
  int to = topBlock(at);
  if (to == -1) to = p[at];
  assert(to != -1);
  for (int i : assassins_at[at]) {
    next_state[to].push_back(i);
  }
}

void processDay() {
  for (int i = 1; i < n; i++) moveAssassins(i);
  swap(assassins_at, next_state);
  next_state.assign(n, {});
}

int main() {
  int t;
  cin >> t;

  while (t--) {
    scanf("%d", &n);
    e.assign(n, {});
    for (int i = 1; i < n; i++) {
      int u, v;
      scanf("%d %d", &u, &v);
      u--, v--;
      e[u].push_back(v);
      e[v].push_back(u);
    }

    p.resize(n);
    dfs(0);

    assassins_at.assign(n, {});
    next_state.assign(n, {});
    for (int i = 0; i < n; i++) {
      if (i and e[i].size() == 1) assassins_at[i].push_back(i);
    }

    int day = 0;
    while (assassins_at[0].empty()) {
      processDay();
      day++;
    }

    sort(assassins_at[0].begin(), assassins_at[0].end());
    printf("%d %d\n", assassins_at[0].size(), day);
    for (int i = 0; i < assassins_at[0].size(); i++) {
      if (i) printf(" ");
      printf("%d", assassins_at[0][i] + 1);
    }
    puts("");
  }

  return 0;
}