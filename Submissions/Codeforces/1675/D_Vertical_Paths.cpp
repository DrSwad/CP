#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> e;
vector<vector<int>> paths;

void dfs(int at) {
  if (e[at].empty()) paths.push_back({at});
  else {
    for (int to : e[at]) dfs(to);
    paths.back().push_back(at);
  }
}

void test_case() {
  cin >> n;

  e = vector<vector<int>>(n);
  int root;
  for (int i = 0; i < n; i++) {
    int p;
    cin >> p;
    p--;
    if (p == i) root = i;
    else e[p].push_back(i);
  }

  paths.clear();
  dfs(root);

  cout << paths.size() << "\n";
  for (auto &path : paths) {
    reverse(path.begin(), path.end());
    cout << path.size() << "\n";
    for (int i = 0; i < path.size(); i++) {
      if (i) cout << " ";
      cout << path[i] + 1;
    }
    cout << "\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    if (cs > 1) cout << "\n";
    test_case();
  }

  return 0;
}