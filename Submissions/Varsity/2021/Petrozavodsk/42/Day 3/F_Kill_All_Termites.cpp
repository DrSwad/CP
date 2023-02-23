#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

vector<int> g[N];
int leaf[N];
int ans = 0;

void dfs(int u, int p = -1) {
  if (g[u].size() == 1) {
    leaf[u] = 1;
    return;
  }

  for (auto v : g[u]) {
    if (v ^ p) {
      dfs(v, u);
      leaf[u] += leaf[v];
    }
  }

  if (leaf[u] >= 2) {
    ans++;
    leaf[u] = 0;
  }
}

int main() {
  int n, x;
  cin >> n;
  for (int i = 2; i <= n; i++) {
    cin >> x;
    g[x].push_back(i);
    g[i].push_back(x);
  }

  if (n <= 2) {
    cout << "1\n"; return 0;
  }

  int root;
  for (int i = 1; i <= n; i++) {
    if (g[i].size() >= 2) {
      root = i; break;
    }
  }

  dfs(root);
  cout << ans << '\n';
}