#include <bits/stdc++.h>
using namespace std;

const int N = 500;

class HopcroftKarp {
private:
  const int INF = 1e8 + 5;
  int n;
  vector<vector<int>> g;
  vector<int> match, dist;
  bool bfs() {
    queue<int> q;
    for (int i = 1; i <= n; ++i) {
      if (!match[i]) dist[i] = 0, q.emplace(i);
      else dist[i] = INF;
    }
    dist[0] = INF;
    while (!q.empty()) {
      int u = q.front(); q.pop();
      if (!u) continue;
      for (int v : g[u - 1]) {
        v++;
        if (dist[match[v]] == INF) {
          dist[match[v]] = dist[u] + 1,
          q.emplace(match[v]);
        }
      }
    }
    return dist[0] != INF;
  }
  bool dfs(int u) {
    if (!u) return true;
    for (int v : g[u - 1]) {
      v++;
      if (dist[match[v]] == dist[u] + 1 and dfs(match[v])) {
        match[u] = v, match[v] = u;
        return true;
      }
    }
    dist[u] = INF;
    return false;
  }
public:
  HopcroftKarp(vector<vector<int>> g) : n(g.size()), g(g) {
    match.resize(n + 1, 0);
    dist.resize(n + 1, 0);
  }
  pair<int, vector<int>> solve() {
    int cnt = 0;
    vector<int> match0(n);
    while (bfs()) {
      for (int i = 1; i <= n; ++i) {
        cnt += !match[i] and dfs(i);
      }
    }
    for (int i = 1; i <= n; i++) match0[i - 1] = match[i] - 1;
    return {cnt, match0};
  }
};
// HopcroftKarp(e).solve(); // e = 0-indexed adjacency-list
// All the edges must be from one part to the other
// Returns (max matching size, 0-indexed matches to each node from left part)

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<bitset<N>> dev_masks(m);
  for (int dev = 0; dev < n; dev++) {
    string access_mask;
    cin >> access_mask;
    for (int doc = 0; doc < m; doc++) {
      if (access_mask[doc] == '1') {
        dev_masks[doc][dev] = true;
      }
    }
  }

  vector<vector<int>> g(2 * m);

  for (int small_doc = 0; small_doc < m; small_doc++) {
    for (int big_doc = 0; big_doc < m; big_doc++) {
      if (small_doc != big_doc and
          (dev_masks[small_doc] & dev_masks[big_doc]) == dev_masks[small_doc] and
          (dev_masks[small_doc] != dev_masks[big_doc] or small_doc < big_doc)
          ) {
        g[small_doc].push_back(m + big_doc);
      }
    }
  }

  auto [cnt, match] = HopcroftKarp(g).solve();
  vector<int> inv_match(m, -1);
  for (int doc = 0; doc < m; doc++) {
    if (match[doc] != -1) {
      match[doc] -= m;
      inv_match[match[doc]] = doc;
    }
  }

  int k = 0;
  vector<vector<int>> dev_levels(n);
  vector<int> doc_groups(m), doc_levels(m);

  for (int doc = 0; doc < m; doc++) {
    if (match[doc] == -1) {
      k++;
      for (int dev = 0; dev < n; dev++) {
        dev_levels[dev].push_back(1);
      }

      int at_doc = doc;
      while (true) {
        doc_groups[at_doc] = k;
        for (int dev = 0; dev < n; dev++) {
          if (dev_masks[at_doc][dev]) {
            dev_levels[dev][k - 1]++;
          }
        }
        at_doc = inv_match[at_doc];
        if (at_doc == -1) break;
      }
    }
  }

  for (int doc = 0; doc < m; doc++) {
    doc_levels[doc] = 1;
    for (int dev = 0; dev < n; dev++) {
      if (!dev_masks[doc][dev]) {
        doc_levels[doc] = max(doc_levels[doc], dev_levels[dev][doc_groups[doc] - 1] + 1);
      }
    }
  }

  cout << k << "\n";
  for (int doc = 0; doc < m; doc++) {
    if (doc) cout << " ";
    cout << doc_groups[doc];
  }
  cout << "\n";
  for (int doc = 0; doc < m; doc++) {
    if (doc) cout << " ";
    cout << doc_levels[doc];
  }
  cout << "\n";
  for (int dev = 0; dev < n; dev++) {
    for (int group = 1; group <= k; group++) {
      if (group > 1) cout << " ";
      cout << dev_levels[dev][group - 1];
    }
    cout << "\n";
  }

  return 0;
}