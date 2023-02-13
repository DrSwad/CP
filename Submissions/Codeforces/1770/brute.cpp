#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int mod = 998244353;
const int inv2 = (mod + 1) / 2;

ll binExp(ll a, ll e, ll m = mod) {
  if (e == -1) e = m - 2;
  ll ret = 1;
  while (e) {
    if (e & 1) ret = ret * a % m;
    a = a * a % m, e >>= 1;
  }
  return ret;
}

int add(int a, int b) {
  int c = a + b;
  return c < mod ? c : c - mod;
}

int mul(int a, int b) {
  return 1ll * a * b % mod;
}

void test_case() {
  int n, k;
  cin >> n >> k;

  vector<bool> init_node_occupied(n, false);
  for (int i = 0; i < k; i++) {
    int a;
    cin >> a;
    init_node_occupied[a - 1] = true;
  }

  int m = n - 1;
  vector<array<int, 2>> edge(m);
  vector<vector<int>> adj(n);

  for (int edge_id = 0; edge_id < m; edge_id++) {
    auto & [u, v] = edge[edge_id];
    cin >> u >> v;
    u--, v--;
    adj[u].push_back(edge_id);
    adj[v].push_back(edge_id);
  }

  auto edge_end = [&](int edge_id, int node_id) {
    return edge[edge_id][1] == node_id;
  };

  auto other_end = [&](int edge_id, int node_id) {
    return edge[edge_id][edge_end(edge_id, node_id) ^ 1];
  };

  vector<array<int, 2>> side(m);
  vector<bool> node_occupied(n);

  function<int(int, int, int)> dfs = [&](int at, int from, int from_edge) {
    int sub = node_occupied[at];
    for (int to_edge : adj[at]) {
      if (to_edge != from_edge) {
        sub += dfs(other_end(to_edge, at), at, to_edge);
      }
    }

    if (from_edge != -1) {
      int at_end = edge_end(from_edge, at);
      side[from_edge][at_end] = sub;
      side[from_edge][at_end ^ 1] = k - sub;
    }

    return sub;
  };

  function<int()> solve = [&]() {
    int sum = 0;
    dfs(0, -1, -1);
    for (int edge_id = 0; edge_id < m; edge_id++) {
      sum = add(sum, mul(side[edge_id][0], side[edge_id][1]));
    }
    return sum;
  };

  vector<int> p2(n);
  p2[0] = 1;
  for (int i = 1; i < n; i++) {
    p2[i] = mul(p2[i - 1], 2);
  }

  int up = 0;
  for (int mask = 0; mask < p2[m]; mask++) {
    node_occupied = init_node_occupied;
    for (int edge_id = 0; edge_id < m; edge_id++) {
      int from = edge[edge_id][0], to = edge[edge_id][1];
      if (mask >> edge_id & 1) swap(from, to);
      if (node_occupied[from] and !node_occupied[to]) {
        swap(node_occupied[from], node_occupied[to]);
      }
    }
    up = add(up, solve());
  }

  int down = mul(p2[m], mul(k, mul(k - 1, inv2)));
  int ans = mul(up, binExp(down, -1));
  cout << ans << "\n";
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}