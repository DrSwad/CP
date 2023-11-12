#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

int add(int a, int b) {
  int c = a + b;
  return c < mod ? c : c - mod;
}

int mul(int a, int b) {
  return 1ll * a * b % mod;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  vector<vector<int>> adj(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  int ans = 0;

  for (int mask = 0; mask < 1 << n; mask++) {
    vector<int> dist(n, n);
    queue<int> q;
    for (int i = 0; i < n; i++) {
      if (mask >> i & 1) {
        dist[i] = 0;
        q.push(i);
      }
    }

    while (!q.empty()) {
      int at = q.front();
      q.pop();
      for (int to : adj[at]) {
        if (dist[to] > dist[at] + 1) {
          dist[to] = dist[at] + 1;
          q.push(to);
        }
      }
    }

    bool okay = true;
    for (int i = 0; i < n; i++) {
      if (dist[i] > k) {
        okay = false;
        break;
      }
    }

    ans += okay;
  }

  cout << ans << "\n";

  return 0;
}