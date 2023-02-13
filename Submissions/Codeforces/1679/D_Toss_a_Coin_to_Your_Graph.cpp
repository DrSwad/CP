#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 2e5 + 5;
const ll K = 2e18;

int n, m;
ll k;
int a[N];
pair<int, int> e[N];
vector<int> adj[N];

ll len[N];

void dfs(int at) {
  len[at] = 0;
  ll mx = 1;

  for (int to : adj[at]) {
    if (len[to] == 0) {
      len[at] = K;
      return;
    }

    if (len[to] == -1) {
      dfs(to);
    }

    mx = max(mx, min(len[to] + 1, K));
  }

  len[at] = mx;
}

bool try_weight(int w) {
  memset(len, -1, sizeof len);
  for (int i = 1; i <= n; i++) {
    adj[i].clear();
  }
  for (int i = 1; i <= m; i++) {
    auto [u, v] = e[i];
    if (a[u] <= w and a[v] <= w) {
      adj[u].push_back(v);
    }
  }

  for (int i = 1; i <= n; i++) {
    if (a[i] <= w) {
      dfs(i);
      if (len[i] >= k) {
        return true;
      }
    }
  }

  return false;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m >> k;

  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }

  for (int i = 1; i <= m; i++) {
    int u, v;
    cin >> u >> v;
    e[i] = {u, v};
  }

  int L = 1, R = 1e9;
  while (L != R) {
    int mid = (L + R) / 2;
    if (try_weight(mid)) R = mid;
    else L = mid + 1;
  }

  if (try_weight(L)) cout << L << "\n";
  else cout << "-1\n";

  return 0;
}