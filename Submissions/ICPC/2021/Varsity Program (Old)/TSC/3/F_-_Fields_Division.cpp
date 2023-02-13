#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 5;

int n, m;
vector<int> e[N];
bool vis[N];
int total_groups;
int group[N];

void dfs(int at) {
  if (vis[at]) return;
  vis[at] = true;
  group[at] = total_groups;

  for (int to : e[at]) {
    dfs(to);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;

  for (int i = 1; i <= m; i++) {
    int u, v;
    cin >> u >> v;
    e[u].push_back(v);
    e[v].push_back(u);
  }

  vis[n] = true;
  for (int i = 1; i <= n; i++) {
    if (!vis[i]) {
      total_groups++;
      dfs(i);
    }
  }

  for (int i = 1; i <= n; i++) {
    cout << (group[i] == group[n - 1] ? 'B' : 'A');
  }
  cout << "\n";

  return 0;
}