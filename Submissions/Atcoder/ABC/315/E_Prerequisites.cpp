#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<vector<int>> adj(n);
  for (int i = 0; i < n; i++) {
    int sz;
    cin >> sz;
    adj[i].resize(sz);
    for (int &j : adj[i]) cin >> j, j--;
  }

  vector<int> ans;
  vector<bool> visited(n, false);

  function<void(int)> dfs =
    [&](int at) {
      visited[at] = true;
      for (int to : adj[at]) {
        if (!visited[to]) dfs(to);
      }
      ans.push_back(at + 1);
    };

  dfs(0);

  ans.pop_back();
  for (int i = 0; i < ans.size(); i++) {
    if (i) cout << " ";
    cout << ans[i];
  }
  cout << "\n";

  return 0;
}