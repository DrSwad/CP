#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int P2 = 20;
const ll INF = 1e18;

void test_case() {
  int n, T;
  cin >> n >> T;

  vector<vector<pair<int, int>>> adj(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    u--, v--;
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
  }

  vector<bool> station(n);
  {
    string s;
    cin >> s;
    for (int i = 0; i < n; i++) {
      station[i] = s[i] == '1';
    }
  }

  int q;
  cin >> q;
  vector<pair<int, int>> queries(q);

  for (auto & [from, to] : queries) {
    cin >> from >> to;
    from--, to--;
  }

  vector<ll> ans(q, INF);

  for (int p2 = 1; p2 <= P2; p2++) {
    vector<ll> cost(n, INF);
    priority_queue<pair<ll, int>> pq;

    for (int i = 0; i < n; i++) {
      if (station[i]) {
        cost[i] = p2 * T;
        pq.emplace(-cost[i], i);
      }
    }

    while (!pq.empty()) {
      auto [at_d, at] = pq.top();
      pq.pop();
      at_d = -at_d;
      if (at_d > cost[at]) continue;

      for (auto [to, w] : adj[at]) {
        ll to_d = at_d + w + (w + (1 << p2) - 1) / (1 << p2);
        if (to_d < cost[to]) {
          cost[to] = to_d;
          pq.emplace(-to_d, to);
        }
      }
    }

    vector<int> h(n);
    vector<ll> pref_big(n), pref_small(n);

    int logn = 32 - __builtin_clz(n);
    vector sp(n, vector(logn, -1));
    vector sp_big(n, vector(logn, -1));
    vector sp_small(n, vector(logn, -1));

    function<void(int, int, int)> dfs =
      [&](int at, int from, int from_w) {
        h[at] = from == -1 ? 0 : h[from] + 1;
        pref_big[at] = from == -1 ? 0 : pref_big[from] + from_w;
        pref_small[at] = from == -1 ? 0 : pref_small[from] + (from_w + (1 << p2) - 1) / (1 << p2);
        sp[at][0] = from;
        sp_big[at][0] = at;
        sp_small[at][0] = at;

        for (auto [to, to_w] : adj[at]) {
          if (to != from) {
            dfs(to, at, to_w);
          }
        }
      };

    dfs(0, -1, 0);

    function<int(int, int)> min_big =
      [&](int i, int j) {
        ll cost_i, cost_j;
        if (h[i] >= h[j]) {
          cost_i = cost[i] + pref_small[i];
          cost_j = (pref_big[i] - pref_big[j]) + cost[j] + pref_small[j];
        }
        else {
          cost_i = (pref_big[j] - pref_big[i]) + cost[i] + pref_small[i];
          cost_j = cost[j] + pref_small[j];
        }
        if (cost_i <= cost_j) return i;
        else return j;
      };

    function<int(int, int)> min_small =
      [&](int i, int j) {
        ll cost_i, cost_j;
        if (h[i] >= h[j]) {
          cost_i = cost[i] + pref_big[i];
          cost_j = (pref_small[i] - pref_small[j]) + cost[j] + pref_big[j];
        }
        else {
          cost_i = (pref_small[j] - pref_small[i]) + cost[i] + pref_big[i];
          cost_j = cost[j] + pref_big[j];
        }
        if (cost_i <= cost_j) return i;
        else return j;
      };

    for (int j = 1; j < logn; j++) {
      for (int i = 0; i < n; i++) {
        sp[i][j] = sp[i][j - 1];
        sp_big[i][j] = sp_big[i][j - 1];
        sp_small[i][j] = sp_small[i][j - 1];

        int mid = sp[i][j - 1];
        if (mid != -1) {
          sp[i][j] = sp[mid][j - 1];
          sp_big[i][j] = min_big(sp_big[i][j - 1], sp_big[mid][j - 1]);
          sp_small[i][j] = min_small(sp_small[i][j - 1], sp_small[mid][j - 1]);
        }
      }
    }

    function<tuple<int, int, int>(int, int)> get_lca =
      [&](int from, int to) {
        int lca;
        int from_big = from;
        int to_small = to;

        if (h[from] != h[to]) {
          for (int i = logn - 1; i >= 0; i--) {
            if (h[from] > h[to]) {
              int new_from = sp[from][i];
              if (new_from != -1 and h[new_from] >= h[to]) {
                from_big = min_big(from_big, sp_big[from][i]);
                from = new_from;
              }
            }
            else if (h[to] > h[from]) {
              int new_to = sp[to][i];
              if (new_to != -1 and h[new_to] >= h[from]) {
                to_small = min_small(to_small, sp_small[to][i]);
                to = new_to;
              }
            }
          }
        }

        if (from == to) {
          lca = from;
          from_big = min_big(from_big, sp_big[from][0]);
          to_small = min_small(to_small, sp_small[to][0]);
        }
        else {
          for (int i = logn - 1; i >= 0; i--) {
            int new_from = sp[from][i];
            int new_to = sp[to][i];
            if (new_from != new_to) {
              from_big = min_big(from_big, sp_big[from][i]);
              to_small = min_small(to_small, sp_small[to][i]);
              from = new_from;
              to = new_to;
            }
          }
          lca = sp[from][0];
          from_big = min_big(from_big, sp_big[from][1]);
          to_small = min_small(to_small, sp_small[to][1]);
        }

        return make_tuple(lca, from_big, to_small);
      };

    for (int qi = 0; qi < q; qi++) {
      auto [from, to] = queries[qi];
      auto [lca, from_big, to_small] = get_lca(from, to);
      ans[qi] = min(ans[qi], pref_big[from] + pref_big[to] - 2ll * pref_big[lca]);
      ans[qi] = min(ans[qi], (pref_big[from] - pref_big[from_big]) + cost[from_big] + (pref_small[from_big] - pref_small[lca]) + (pref_small[to] - pref_small[lca]));
      ans[qi] = min(ans[qi], (pref_big[from] - pref_big[lca]) + (pref_big[to_small] - pref_big[lca]) + cost[to_small] + (pref_small[to] - pref_small[to_small]));
    }
  }

  for (int qi = 0; qi < q; qi++) {
    cout << ans[qi] << "\n";
  }
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