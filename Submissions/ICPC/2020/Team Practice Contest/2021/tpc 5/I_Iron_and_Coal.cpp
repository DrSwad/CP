#include <bits/stdc++.h>
using namespace std;

const int INF = 1e6 + 5;
const int N = 1e5 + 5;

int nn;
int n[2];
vector<int> a[3];
vector<int> e[N], re[N];
int dist[3][N];

void bfs(int it, int *dist, vector<int> *e) {
  queue<pair<int, int>> q;
  for (int st : a[it]) {
    q.push({0, st});
    dist[st] = 0;
  }

  while (!q.empty()) {
    auto [cdist, at] = q.front();
    q.pop();
    if (cdist > dist[at]) continue;

    for (int to : e[at]) {
      if (dist[to] > cdist + 1) {
        dist[to] = cdist + 1;
        q.push({dist[to], to});
      }
    }
  }
}

int main() {
  scanf("%d %d %d", &nn, &n[0], &n[1]);

  for (int it = 0; it < 2; it++) {
    a[it].resize(n[it]);
    for (int i = 0; i < n[it]; i++) {
      scanf("%d", &a[it][i]);
      a[it][i]--;
    }
  }
  a[2].push_back(0);

  for (int i = 0; i < nn; i++) {
    int m;
    scanf("%d", &m);
    int from = i;

    for (int j = 0; j < m; j++) {
      int to;
      scanf("%d", &to);
      to--;
      e[from].push_back(to);
      re[to].push_back(from);
    }
  }

  for (int it = 0; it < 3; it++) {
    fill(begin(dist[it]), end(dist[it]), INF);
  }

  bfs(0, dist[0], re);
  bfs(1, dist[1], re);
  bfs(2, dist[2], e);

  int ans = INF;
  for (int i = 0; i < nn; i++) {
    ans = min(ans, dist[0][i] + dist[1][i] + dist[2][i]);
  }

  cout << (ans < INF ? to_string(ans) : "impossible") << endl;

  return 0;
}