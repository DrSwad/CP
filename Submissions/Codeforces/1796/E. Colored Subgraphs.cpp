#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<vector<int>> adj(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;

    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  auto check = [&](int min_len) {
    vector<int> degree(n, 0);
    for (int i = 0; i < n; i++) {
      degree[i] = adj[i].size();
    }
    vector<int> path_len(n, 1);
    vector<bool> done(n, false);

    auto is_hanging = [&](int node) {
      if(done[node]) return false;
      if (degree[node] > 1) return false;
      if (path_len[node] >= min_len) return true;
      if (degree[node] == 0) return false;
      int parent = -1;
      for (int nxt : adj[node]) {
        if (!done[nxt]) {
          parent = nxt;
          break;
        }
      }
      return degree[parent] <= 2;
    };

    queue<int> hanging_leaves;
    for (int i = 0; i < n; i++) {
      if (is_hanging(i)) hanging_leaves.push(i);
    }

    while (!hanging_leaves.empty()) {
      int at = hanging_leaves.front();
      if (!done[at] and !is_hanging(at)) break;
      hanging_leaves.pop();
      if (done[at]) continue;

      assert(degree[at] <= 1);
      degree[at] = 0;
      done[at] = true;

      int parent = -1;
      for (int nxt : adj[at]) {
        if (!done[nxt]) {
          parent = nxt;
          break;
        }
      }

      if (parent != -1) {
        degree[parent]--;
        if (degree[parent] <= 1) {
          path_len[parent] = min(min_len, path_len[parent] + path_len[at]);
          if (is_hanging(parent)) {
            hanging_leaves.push(parent);
          }
        }
        else if (degree[parent] == 2) {
          for (int nxt : adj[parent]) {
            if (!done[nxt] and is_hanging(nxt)) {
              hanging_leaves.push(nxt);
            }
          }
        }
      }
    }

    return accumulate(done.begin(), done.end(), 0) == n;
  };

  int L = 1, R = n + 1;
  while (L < R - 1) {
    int mid = (L + R) / 2;
    if (check(mid)) L = mid;
    else R = mid;
  }

  cout << L << "\n";
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
