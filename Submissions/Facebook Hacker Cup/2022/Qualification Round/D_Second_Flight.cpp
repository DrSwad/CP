#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 2e5 + 5;
const int HEAVY = 450;

void test_case() {
  int n, m, q;
  cin >> n >> m >> q;

  vector<unordered_map<int, int>> e(n);
  while (m--) {
    int u, v, c;
    cin >> u >> v >> c;
    u--, v--;
    e[u][v] = c;
    e[v][u] = c;
  }

  vector<int> heavy;
  unordered_map<ll, ll> mp;

  for (int i = 0; i < n; i++) {
    if (e[i].size() >= HEAVY) {
      heavy.push_back(i);
    }
    else {
      for (auto [u, cu] : e[i]) {
        for (auto [v, cv] : e[i]) {
          mp[1ll * u * N + v] += min(cu, cv);
        }
      }
    }
  }

  while (q--) {
    int u, v;
    cin >> u >> v;
    u--, v--;

    ll id = 1ll * u * N + v;
    long long ans = mp.find(id) != mp.end() ? mp[id] : 0;
    for (int i : heavy) {
      if (e[i].find(u) != e[i].end() and e[i].find(v) != e[i].end()) {
        ans += min(e[i][u], e[i][v]);
      }
    }
    ans += 2ll * e[u][v];

    cout << " " << ans;
  }
  cout << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ":";
    test_case();
  }

  return 0;
}