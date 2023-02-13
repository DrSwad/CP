#include <bits/stdc++.h>
using namespace std;

int n, k;
int st, en;
vector<bool> should_visit;
vector<vector<int>> e;

tuple<int, bool, bool> dfs(int at, int from) {
  int ret_time = 0;
  bool need_visits = should_visit[at];
  bool has_en = en == at;

  for (int to : e[at]) {
    if (to != from) {
      auto [ret_time2, need_visits2, has_en2] = dfs(to, at);

      if (need_visits2 or has_en2) ret_time += ret_time2;
      if (has_en2) ret_time++;
      else if (need_visits2) ret_time += 2;

      need_visits = need_visits or need_visits2;
      has_en = has_en or has_en2;
    }
  }

  return {ret_time, need_visits, has_en};
}

void test_case() {
  cin >> n >> k;
  cin >> st >> en;
  st--, en--;

  should_visit.assign(n, false);
  for (int i = 0; i < k; i++) {
    int a;
    cin >> a;
    a--;
    should_visit[a] = true;
  }

  e = vector<vector<int>>(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    e[u].push_back(v);
    e[v].push_back(u);
  }

  cout << get<0>(dfs(st, -1)) << "\n";
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