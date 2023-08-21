#include <bits/stdc++.h>
using namespace std;

const int C = 26;
const int INF = 1e5;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string s;
  cin >> s;
  int n = s.length();

  int nodes = n - 1;
  vector<vector<pair<int, int>>> adj(nodes);
  int pairs = 0;
  vector pair_node(C, vector(C, -1));

  for (int c1 = 0; c1 < C; c1++) {
    for (int c2 = 0; c2 < C; c2++) {
      pairs++;
      pair_node[c1][c2] = nodes++;
      adj.emplace_back();
    }
  }

  for (int i = 0; i < n - 1; i++) {
    if (i - 1 >= 0) {
      adj[i].emplace_back(i - 1, 1);
      adj[i - 1].emplace_back(i, 1);
    }

    int c1 = s[i] - 'a';
    int c2 = s[i + 1] - 'a';
    adj[i].emplace_back(pair_node[c1][c2], 0);
    adj[pair_node[c1][c2]].emplace_back(i, 1);
  }

  vector dist(pairs, vector(nodes, INF));

  for (int pair_id = 0; pair_id < pairs; pair_id++) {
    int source = (n - 1) + pair_id;

    vector<int> &cur_dist = dist[pair_id];
    deque<int> q;
    cur_dist[source] = 0;
    q.emplace_front(source);

    while (!q.empty()) {
      int at = q.front();
      q.pop_front();

      for (auto [to, w] : adj[at]) {
        if (cur_dist[to] > cur_dist[at] + w) {
          cur_dist[to] = cur_dist[at] + w;
          if (w) q.push_back(to);
          else q.push_front(to);
        }
      }
    }
  }

  int q;
  cin >> q;

  while (q--) {
    int from, to;
    cin >> from >> to;
    from--, to--;

    int ans = abs(from - to);
    for (int pair_id = 0; pair_id < pairs; pair_id++) {
      ans = min(ans, dist[pair_id][from] + dist[pair_id][to] - 1);
    }

    cout << ans << "\n";
  }

  return 0;
}