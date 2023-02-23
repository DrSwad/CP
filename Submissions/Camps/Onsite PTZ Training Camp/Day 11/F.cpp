#include <bits/stdc++.h>

using namespace std;

const int N = 1e4 + 5;
const int inf = 1e8;

int parent[N];
int dis[3][N];
int min_path[3][N];

vector<pair<int, int>> g[N];

void djkstra(int src, int idx) {
  fill(dis[idx], dis[idx] + N, inf);
  fill(min_path[idx], min_path[idx] + N, N);

  dis[idx][src] = 0;
  min_path[idx][src] = src;

  priority_queue<pair<int, int>> PQ;
  PQ.push({0, -src});

  while (!PQ.empty()) {
    auto [d, u] = PQ.top(); PQ.pop();
    d = -d;
    u = -u;

    if (dis[idx][u] < d) continue;

    for (auto [v, w] : g[u]) {

      int relax_d = dis[idx][u] + w, relax_path = min(v, min_path[idx][u]);

      if (dis[idx][v] > relax_d or (dis[idx][v] == relax_d and min_path[idx][v] > relax_path)) {
        dis[idx][v] = relax_d;
        PQ.push({-dis[idx][v], -v});
        min_path[idx][v] = relax_path;
      }
    }
  }
}

int main() {

  ios::sync_with_stdio(false);
  cin.tie(NULL);

  int n, a, b, c;

  cin >> n >> a >> b >> c;

  for (int i = 1; i <= n; i++) parent[i] = i;

  vector<int> A(a), B(b), C(c);

  for (int i = 0; i < a; i++) {
    cin >> A[i];
  }

  for (int i = 0; i < b; i++) {
    cin >> B[i];
  }

  for (int i = 0; i < c; i++) {
    cin >> C[i];
  }

  sort(A.begin(), A.end());
  sort(B.begin(), B.end());
  sort(C.begin(), C.end());

  for (int i = 1; i < a; i++) {
    parent[A[i]] = A[0];
  }

  for (int i = 1; i < b; i++) {
    parent[B[i]] = B[0];
  }

  for (int i = 1; i < c; i++) {
    parent[C[i]] = C[0];
  }

  int m, u, v;
  cin >> m;

  for (int i = 0; i  < m; i++) {
    cin >> u >> v;

    u = parent[u];
    v = parent[v];

    if (u == v) continue;

    g[u].push_back({v, 1});
    g[v].push_back({u, 1});
  }

  for (int i = 1; i <= n; i++) {
    sort(g[i].begin(), g[i].end());
  }
  djkstra(A[0], 0);
  djkstra(B[0], 1);
  djkstra(C[0], 2);

  pair<int, int> ans(inf, N);

  for (int i = 1; i <= n; i++) {
    int cur_dis = dis[0][i] + dis[1][i] + dis[2][i];
    int cur_node = min({min_path[0][i], min_path[1][i], min_path[2][i]});
    ans = min(ans, make_pair(cur_dis, cur_node));

    // cout << i << ' ' << cur_dis << ' ' << cur_node << endl;
  }

  assert(ans.first != inf);
  assert(ans.second != N);

  cout << ans.first << ' ' << ans.second << '\n';

  return 0;
}