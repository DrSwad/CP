#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<vector<int>> adj(n);
  vector<pair<int, int>> e;
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    e.emplace_back(u, v);
    adj[u].push_back(i);
    adj[v].push_back(i);
  }

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<int> cmp_a = a;
  cmp_a.push_back(0);
  sort(cmp_a.begin(), cmp_a.end());
  cmp_a.resize(unique(cmp_a.begin(), cmp_a.end()) - cmp_a.begin());
  for (int &i : a) {
    i = lower_bound(cmp_a.begin(), cmp_a.end(), i) - cmp_a.begin();
  }

  function<void(int, int, function<void(int, int)>)> dfs =
    [&](int at, int from, function<void(int, int)> f) {
      for (int e_id : adj[at]) {
        int to = e[e_id].first + e[e_id].second - at;
        if (to != from) dfs(to, at, f);
      }
      f(at, from);
    };

  vector<int> freq(cmp_a.size(), 0);
  set<int> twos;
  auto add = [&](int val) { freq[val]++; if (freq[val] == 2) twos.insert(val); };
  auto remove = [&](int val) { if (freq[val] == 2) twos.erase(val); freq[val]--; };

  vector<int> sub(n);
  dfs(
    0,
    -1,
    [&](int at, int from) {
      sub[at] = 1;
      for (int e_id : adj[at]) {
        int to = e[e_id].first + e[e_id].second - at;
        if (to != from) sub[at] += sub[to];
      }
    }
  );

  vector<int> up(n - 1);
  {
    function<void(int, int)> dsu =
      [&](int at, int from) {
        add(a[at]);

        int big_size = 0, big_child = -1, big_edge = -1;
        for (int e_id : adj[at]) {
          int to = e[e_id].first + e[e_id].second - at;
          if (to == from) continue;
          if (sub[to] > big_size) {
            big_size = sub[to];
            big_child = to;
            big_edge = e_id;
          }
        }

        for (int e_id : adj[at]) {
          int to = e[e_id].first + e[e_id].second - at;
          if (to == from) continue;
          if (to != big_child) {
            dfs(to, at, [&](int to, int at) { add(a[to]); });
          }
        }

        if (big_child != -1) {
          up[big_edge] = twos.empty() ? 0 : *prev(twos.end());
          dsu(big_child, at);
        }

        for (int e_id : adj[at]) {
          int to = e[e_id].first + e[e_id].second - at;
          if (to == from) continue;
          if (to != big_child) {
            dfs(to, at, [&](int to, int at) { remove(a[to]); });
            up[e_id] = twos.empty() ? 0 : *prev(twos.end());
            dsu(to, at);
          }
        }
      };

    dsu(0, -1);
  }

  fill(freq.begin(), freq.end(), 0);
  twos.clear();

  vector<int> down(n - 1);
  {
    function<void(int, int)> dsu =
      [&](int at, int from) {
        int big_size = 0, big_child = -1, big_edge = -1;
        for (int e_id : adj[at]) {
          int to = e[e_id].first + e[e_id].second - at;
          if (to == from) continue;
          if (sub[to] > big_size) {
            big_size = sub[to];
            big_child = to;
            big_edge = e_id;
          }
        }

        for (int e_id : adj[at]) {
          int to = e[e_id].first + e[e_id].second - at;
          if (to == from) continue;
          if (to != big_child) {
            dsu(to, at);
            down[e_id] = twos.empty() ? 0 : *prev(twos.end());
            dfs(to, at, [&](int to, int at) { remove(a[to]); });
          }
        }

        if (big_child != -1) {
          dsu(big_child, at);
          down[big_edge] = twos.empty() ? 0 : *prev(twos.end());
        }

        for (int e_id : adj[at]) {
          int to = e[e_id].first + e[e_id].second - at;
          if (to == from) continue;
          if (to != big_child) {
            dfs(to, at, [&](int to, int at) { add(a[to]); });
          }
        }

        add(a[at]);
      };

    dsu(0, -1);
  }

  for (int i = 0; i < n - 1; i++) {
    int ans = cmp_a[max(up[i], down[i])];
    cout << ans << "\n";
  }

  return 0;
}