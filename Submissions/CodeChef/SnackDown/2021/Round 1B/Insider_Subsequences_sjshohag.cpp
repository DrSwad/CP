#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 9;

int a[N], b[N], f[N], g[N], n;
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t; cin >> t;
  while (t--) {
    cin >> n;
    set<int> se;
    vector<pair<int, int>> v;
    vector<int> c;
    int z = n;
    a[0] = -1;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      if (a[i] != a[i - 1]) c.push_back(a[i]);
      f[i] = 2e9;
      g[i] = 0;
    }
    n = c.size();
    for (int i = 1; i <= n; i++) {
      a[i] = c[i - 1];
    }
    for (int i = 1; i <= n; i++) {
      se.insert(a[i] + 1);
      se.insert(a[i] - 1);
      b[i] = 1;
      v.push_back({a[i], i});
    }
    sort(v.begin(), v.end());
    int i = 0, ans = 0;
    for (auto x: se) {
      int l = -1;
      while (i < n) {
        if (v[i].first > x) break;
        int j = v[i].second;
        if (j > 1 and (b[j] ^ b[j - 1])) --ans;
        if (j < n and (b[j] ^ b[j + 1])) --ans;
        if (v[i].first < x) b[j] = 0;
        else {
          b[j] = j == 1 ? b[j + 1] : b[j - 1];
          if (l == -1) l = i;
        }
        if (j > 1 and (b[j] ^ b[j - 1])) ++ans;
        if (j < n and (b[j] ^ b[j + 1])) ++ans;
        ++i;
      }
      f[ans + 1] = min(f[ans + 1], x);
      g[ans + 1] = max(g[ans + 1], x);
      if (l != -1) i = l;
    }
    for (int i = z; i >= 2; i--) {
      f[i - 1] = min(f[i - 1], f[i]);
      g[i - 1] = max(g[i - 1], g[i]);
    }
    for (int i = 2; i <= z; i++) {
      if (f[i] >= 2e9 - 1) f[i] = -1;
      if (i > 2) cout << ' ';
      cout << f[i];
    } cout << '\n';
    for (int i = 2; i <= z; i++) {
      if (g[i] <= 0) g[i] = -1;
      if (i > 2) cout << ' ';
      cout << g[i];
    } cout << '\n';
  }
  return 0;
}