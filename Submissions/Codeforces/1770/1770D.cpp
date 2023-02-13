#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

int add(int a, int b) {
  return (a + b) % MOD;
}

int mul(int a, int b) {
  return 1ll * a * b % MOD;
}

void test_case() {
  int n;
  cin >> n;

  vector<set<int>> adj(2 * n);
  int ans = 1;

  auto add_edge = [&](int a, int b) {
    adj[a].insert(n + b);
    adj[n + b].insert(a);
  };

  vector<int> a(n), b(n);
  for (int &i : a) cin >> i, i--;
  for (int &i : b) cin >> i, i--;

  for (int i = 0; i < n; i++) {
    if (a[i] == b[i]) {
      ans = mul(ans, n);
      add_edge(i, a[i]);
    }
    else {
      add_edge(i, a[i]);
      add_edge(i, b[i]);
    }
  }

  vector<int> match(2 * n, -1);
  queue<pair<int, int>> q;
  for (int i = 0; i < 2 * n; i++) {
    if (adj[i].empty()) {
      cout << "0\n";
      return;
    }
    if (adj[i].size() == 1) {
      // debug(i);
      q.push({i, *adj[i].begin()});
    }
  }

  while (!q.empty()) {
    auto [u, v] = q.front();
    // debug(u, v);
    q.pop();
    if ((match[u] != -1 and match[u] != v) or (match[v] != -1 and match[v] != u)) {
      cout << "0\n";
      return;
    }
    match[u] = v, match[v] = u;
    for (int w : adj[u]) {
      if (w != v and match[w] == -1) {
        adj[w].erase(u);
        if (adj[w].empty()) {
          cout << "0\n";
          return;
        }
        if (adj[w].size() == 1) {
          // debug(u, w);
          q.push({w, *adj[w].rbegin()});
        }
      }
    }
    for (int w : adj[v]) {
      if (w != u and match[w] == -1) {
        adj[w].erase(v);
        if (adj[w].empty()) {
          cout << "0\n";
          return;
        }
        if (adj[w].size() == 1) {
          // debug(v, w);
          q.push({w, *adj[w].rbegin()});
        }
      }
    }
  }

  // debug(match);

  vector<bool> vis(2 * n, false);
  for (int i = 0; i < 2 * n; i++) {
    if (match[i] != -1 or vis[i]) continue;
    ans = mul(ans, 2);

    int at = i;
    assert(adj[at].size() == 2);
    int prv = *adj[at].rbegin();
    while (!vis[at]) {
      vis[at] = true;
      int nxt = *adj[at].rbegin() + *adj[at].begin() - prv;
      assert(adj[nxt].size() == 2);
      prv = at;
      at = nxt;
    }
  }

  cout << ans << "\n";
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