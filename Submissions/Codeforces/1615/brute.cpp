#include <bits/stdc++.h>
using namespace std;
//dengyaotriangle!
const int maxn = 200005;

int n, k;
vector<int> adj[maxn];
priority_queue<int> pq[maxn];

void dfs(int u, int f) {
  for (int v:adj[u]) if (v != f) {
      dfs(v, u);
      if (pq[u].size() < pq[v].size()) swap(pq[u], pq[v]);
      while (!pq[v].empty()) {
        pq[u].emplace(pq[v].top()); pq[v].pop();
      }
    }
  if (pq[u].empty()) pq[u].emplace(1);
  else{
    int z = pq[u].top() + 1;
    pq[u].pop(); pq[u].emplace(z);
  }
}
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> n >> k;
  for (int i = 1; i < n; i++) {
    int u, v; cin >> u >> v;
    adj[u].emplace_back(v);
    adj[v].emplace_back(u);
  }
  dfs(1, 0);
  long long ans = LLONG_MIN;
  int s = 0;
  for (int i = 0; i <= k; i++) {
    int c = min(n / 2, n - s);
    ans = max(ans, (n - i - c) * (long long)(i - c));
    if (!pq[1].empty()) {
      s += pq[1].top(); pq[1].pop();
    }
  }
  cout << ans;
  return 0;
}