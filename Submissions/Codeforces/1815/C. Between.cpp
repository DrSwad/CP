#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, m;
  cin >> n >> m;

  vector<vector<int>> adj(n);

  while (m--) {
    int to, from;
    cin >> to >> from;
    to--, from--;
    adj[from].push_back(to);
  }

  vector<int> dist(n, -1);
  vector<vector<int>> nodes_at_dist(n);

  // bfs
  {
    queue<int> q;
    dist[0] = 0;
    q.push(0);
    while (!q.empty()) {
      int at = q.front();
      q.pop();
      for (int to : adj[at]) {
        if (dist[to] != -1) continue;
        dist[to] = dist[at] + 1;
        q.push(to);
      }
    }

    for (int i = 0; i < n; i++) {
      if (dist[i] == -1) {
        cout << "INFINITE\n";
        return;
      }
      nodes_at_dist[dist[i]].push_back(i);
    }
  }

  while (nodes_at_dist.back().empty()) {
    nodes_at_dist.pop_back();
  }

  int max_dist = nodes_at_dist.size();

  vector<int> rem(max_dist);
  for (int i = 0; i < max_dist; i++) {
    rem[i] = i + 1;
  }

  vector<int> ans;

  while (rem.back()) {
    for (int d = max_dist - 1; d >= 0; d--) {
      for (int i = 0; i < nodes_at_dist[d].size(); i++) {
        ans.push_back(nodes_at_dist[d][i] + 1);
      }

      rem[d]--;
      if (rem[d] == 0) break;
    }
  }

  cout << "FINITE\n";
  cout << ans.size() << "\n";
  for (int i = 0; i < ans.size(); i++) {
    if (i) cout << " ";
    cout << ans[i];
  }
  cout << "\n";
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
