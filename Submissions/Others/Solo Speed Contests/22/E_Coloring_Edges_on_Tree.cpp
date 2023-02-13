#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int n;
pair<int, int> e[N];
vector<int> adj[N];
int colors;
int color[N];

void dfs(int at = 1, int pe = -1) {
  int at_color = 1;
  for (int ei : adj[at]) {
    if (ei != pe) {
      auto [u, v] = e[ei];
      int to = at ^ u ^ v;
      if (pe != -1 and color[pe] == at_color) at_color++;
      color[ei] = at_color++;
      dfs(to, ei);
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;

  vector<int> deg(n, 0);
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    deg[u - 1]++;
    deg[v - 1]++;
    e[i] = {u, v};
    adj[u].push_back(i);
    adj[v].push_back(i);
  }

  colors = *max_element(deg.begin(), deg.end());
  dfs();

  cout << colors << "\n";
  for (int i = 1; i < n; i++) {
    cout << color[i] << "\n";
  }

  return 0;
}