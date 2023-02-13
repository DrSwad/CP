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

  vector<bool> node_occupied(n, false);
  for (int i = 0; i < k; i++) {
    int a;
    cin >> a;
    node_occupied[a - 1] = true;
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

  dfs(0, -1, -1);

  vector<array<int, 3>> node_dp(n);
  for (int node_id = 0; node_id < n; node_id++) {
    node_dp[node_id][0] = node_occupied[node_id] == 0;
    node_dp[node_id][1] = node_occupied[node_id] == 1;
    node_dp[node_id][2] = 0;
  }

  vector<array<array<int, 3>, 2>> edge_dp(m);

  for (int edge_id = 0; edge_id < m; edge_id++) {
    for (int at_end = 0; at_end < 2; at_end++) {
      int node_id = edge[edge_id][at_end];
      edge_dp[edge_id][at_end] = node_dp[node_id];
    }
  }

  for (int edge_id = 0; edge_id < m; edge_id++) {
    edge_dp[edge_id][0] = node_dp[edge[edge_id][0]];
    edge_dp[edge_id][1] = node_dp[edge[edge_id][1]];

    for (int at_end = 0; at_end < 2; at_end++) {
      array<int, 3> &cdp = node_dp[edge[edge_id][at_end]];

      int child_end = at_end ^ 1;
      array<int, 3> ndp{};
      ndp[2] = cdp[2] + 1 + edge_dp[edge_id][child_end][2];

      for (int at_state = 0; at_state < 2; at_state++) {
        for (int child_state = 0; child_state < 2; child_state++) {
          for (int dir = 0; dir < 2; dir++) {
            int new_state = (at_state == 1 and (child_state != 0 or dir != 0)) or (at_state == 0 and child_state == 1 and dir == 1);
            ndp[new_state] = add(ndp[new_state], mul(cdp[at_state], edge_dp[edge_id][child_end][child_state]));
          }
        }
      }

      swap(cdp, ndp);
    }
  }

  vector<int> p2(n);
  p2[0] = 1;
  for (int i = 1; i < n; i++) {
    p2[i] = mul(p2[i - 1], 2);
  }

  int up = 0;
  for (int edge_id = 0; edge_id < m; edge_id++) {
    array<int, 3> &dp0 = edge_dp[edge_id][0];
    array<int, 3> &dp1 = edge_dp[edge_id][1];
    int edge_rem = m - dp0[2] - dp1[2] - 1;

    for (int state0 = 0; state0 < 2; state0++) {
      for (int state1 = 0; state1 < 2; state1++) {
        for (int dir01 = 0; dir01 < 2; dir01++) {
          int mult = mul(p2[edge_rem], mul(dp0[state0], dp1[state1]));
          int side0 = side[edge_id][0];
          int side1 = side[edge_id][1];
          if (dir01 == 1 and state0 == 1 and state1 == 0) side0--, side1++;
          if (dir01 == 0 and state0 == 0 and state1 == 1) side0++, side1--;
          up = add(up, mul(mult, mul(side0, side1)));
        }
      }
    }
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