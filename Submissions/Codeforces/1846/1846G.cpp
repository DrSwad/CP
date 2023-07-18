#include <bits/stdc++.h>
using namespace std;

const int N = 10;

void test_case() {
  int n, m;
  cin >> n >> m;

  int st;
  {
    string s;
    cin >> s;
    st = bitset<N>(s).to_ulong();
  }

  vector<int> d(m), remove(m), add(m);
  for (int i = 0; i < m; i++) {
    cin >> d[i];
    string s;
    cin >> s;
    remove[i] = bitset<N>(s).to_ulong();
    cin >> s;
    add[i] = bitset<N>(s).to_ulong();
  }

  vector<vector<pair<int, int>>> adj(1 << n);
  for (int mask = 0; mask < 1 << n; mask++) {
    for (int i = 0; i < m; i++) {
      int to_mask = (mask & (~remove[i])) | add[i];
      adj[mask].emplace_back(to_mask, d[i]);
    }
  }

  vector<int> dist(1 << n, INT_MAX);
  dist[st] = 0;
  priority_queue<pair<int, int>> pq;
  pq.push({0, st});

  while (!pq.empty()) {
    auto [at_dist, at] = pq.top(); pq.pop();
    at_dist = -at_dist;
    if (at_dist > dist[at]) continue;

    for (auto [to, w] : adj[at]) {
      if (dist[to] > at_dist + w) {
        dist[to] = at_dist + w;
        pq.push(make_pair(-dist[to], to));
      }
    }
  }

  cout << (dist[0] == INT_MAX ? -1 : dist[0]) << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}