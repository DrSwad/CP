#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 5e5 + 5;

int n;
vector<pair<int, int>> e[N];
int sub[N];
map<int, vector<pair<int, int>>> mp[N];
ll ans;

void dfs(int v, int p, int w) {
  sub[v] = 1;
  int mx = 0, big_child = 0;
  for (auto [u, w2] : e[v]) {
    if (u != p) {
      dfs(u, v, w2);
      sub[v] += sub[u];
      if (sub[u] > mx) {
        mx = sub[u];
        big_child = u;
      }
    }
  }

  swap(mp[v], mp[big_child]);

  for (auto [u, _] : e[v]) {
    if (u != p and u != big_child) {
      for (auto [w2, subs] : mp[u]) {
        for (auto sub : subs) {
          mp[v][w2].push_back(sub);
        }
      }
    }
  }

  vector<int> process_w;
  if (w) process_w.push_back(w);
  else {
    for (auto [w2, _] : mp[v]) {
      process_w.push_back(w2);
    }
  }

  for (int cw : process_w) {
    int tot = sub[v];
    for (auto [sub_sz, _] : mp[v][cw]) {
      tot -= sub_sz;
    }
    for (auto [_, cnt] : mp[v][cw]) {
      ans += (ll)tot * cnt;
    }
    mp[v][cw].clear();
    mp[v][cw].push_back({sub[v], tot});
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  for (int i = 1; i < n; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    e[u].push_back({v, w});
    e[v].push_back({u, w});
  }

  dfs(1, 0, 0);

  cout << ans << "\n";

  return 0;
}