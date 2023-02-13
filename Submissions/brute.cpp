    #include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
const ll mx = 10005;
const ll Log = 15;
ll immediateParentOf[mx];
ll levelOf[mx], levelCostOf[mx], visited[mx];

void dfs(ll i, vector<pair<ll, ll>> v[]) {
  for (auto u: v[i]) {
    if (visited[u.first]) continue;
    visited[u.first] = 1;
    levelOf[u.first] = levelOf[i] + 1;
    levelCostOf[u.first] = levelCostOf[i] + u.second;
    immediateParentOf[u.first] = i;
    dfs(u.first, v);
  }
}

int main() {
  //    freopen("input.txt", "r", stdin);
  //    freopen("output.txt", "w", stdout);
  ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  ll t;
  cin >> t;
  while (t--) {
    ll n;
    cin >> n;
    ll sparseTable[n + 1][Log + 1];
    // clean
    for (ll i = 0; i <= n; ++i) {
      for (ll j = 0; j <= Log; ++j) {
        sparseTable[i][j] = -1;
      }
      levelOf[i] = 0;
      levelCostOf[i] = 0;
      visited[i] = 0;
      immediateParentOf[i] = -1;
    }
    vector<pair<ll, ll>> v[n + 1];

    for (ll i = 0; i < n - 1; ++i) {
      ll a, b, c;
      cin >> a >> b >> c;
      v[a].emplace_back(b, c);
      v[b].emplace_back(a, c);
    }
    visited[1] = 1;
    dfs(1, v);
    for (ll i = 1; i <= n; ++i) {
      sparseTable[i][0] = immediateParentOf[i];
    }
    for (ll j = 1; (1 << j) <= n; ++j) {
      for (ll i = 1; i <= n; ++i) {
        if (sparseTable[i][j - 1] != -1) {
          sparseTable[i][j] = sparseTable[sparseTable[i][j - 1]][j - 1];
        }
      }
    }
    while (1) {
      string s;
      cin >> s;
      if (s == "DONE") break;

      ll p, q, P, Q, dist = 0;
      cin >> p >> q;
      dist += levelCostOf[p] + levelCostOf[q];
      P = p, Q = q;
      if (levelOf[p] < levelOf[q]) swap(p, q);
      for (ll i = Log; i >= 0; i--) {
        if (levelOf[p] - (1 << i) >= levelOf[q]) {
          p = sparseTable[p][i];
        }
      }
      ll lca;
      for (ll i = Log; i >= 0; i--) {
        if (sparseTable[p][i] != -1 && sparseTable[p][i] != sparseTable[q][i]) {
          p = sparseTable[p][i], q = sparseTable[q][i];
        }
      }
      lca = immediateParentOf[p];
      if (p == q) lca = p;

      p = P, q = Q;

      if (s == "DIST") {
        dist -= levelCostOf[lca];
        dist -= levelCostOf[lca];
        cout << dist << endl;
      }
      else {
        ll k, targetLevel;
        cin >> k;
        k--;
        if (levelOf[p] - levelOf[lca] >= k) {}
        else {
          k -= levelOf[p] - levelOf[lca];
          k = levelOf[q] - levelOf[lca] - k;
          p = q;
        }
        if (k < 0) p = -1;
        else {
          targetLevel = levelOf[p] - k;
          for (ll i = Log; i >= 0; i--) {
            if (levelOf[p] - (1 << i) >= targetLevel) {
              p = sparseTable[p][i];
            }
          }
        }
        cout << p << endl;
      }
    }
    cout << endl;
  }
}