#include <bits/stdc++.h>
using namespace std;

struct DSU {
  int n;
  vector<int> p; // root: -1 * component size, otherwise: parent
  DSU(int n) : n(n), p(n, -1) {}
  bool same(int a, int b) { return root(a) == root(b); }
  int root(int a) { return p[a] < 0 ? a : (p[a] = root(p[a])); }
  int size(int a) { return -p[root(a)]; }
  bool merge(int a, int b) {
    int x = root(a), y = root(b);
    if (x == y) return false;
    if (-p[x] < -p[y]) swap(x, y);
    p[x] += p[y];
    p[y] = x;
    return true;
  }
};

const int N = 1e6 + 5;

int n, q;
vector<int> ei[N], eo[N];
bool vis[N];
DSU dsu(2 * N);
int dsu_ind[N];
map<int, int> rem_to_ind, ind_to_rem;

void dfs(int at, int rem) {
  if (rem_to_ind.find(rem) == rem_to_ind.end()) {
    int ind = rem_to_ind.size();
    rem_to_ind[rem] = ind;
    ind_to_rem[ind] = rem;
  }

  int ind = rem_to_ind[rem];

  if (dsu_ind[at] != -1) dsu.merge(dsu_ind[at], ind);
  else dsu_ind[at] = ind;

  if (vis[at]) return;
  vis[at] = true;

  for (int to : eo[at]) {
    dfs(to, rem + 1);
  }
  for (int from : ei[at]) {
    dfs(from, rem - 1);
  }
}

void reset_dsu() {
  int sz = rem_to_ind.size();
  for (int i = 0; i < sz; i++) {
    dsu.p[i] = -1;
  }
  rem_to_ind.clear();
  ind_to_rem.clear();
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> q;

  for (int i = 0; i < q; i++) {
    int x, y;
    cin >> x >> y;
    x--, y--;

    eo[x].push_back(y);
    ei[y].push_back(x);
  }

  int cycle_gcd = -1;
  memset(dsu_ind, -1, sizeof dsu_ind);

  for (int i = 0; i < n; i++) {
    if (!vis[i]) {
      dfs(i, 0);

      int sz = rem_to_ind.size();
      for (int i = 0; i < sz; i++) {
        if (dsu.root(i) != i) {
          int rem1 = ind_to_rem[dsu.root(i)];
          int rem2 = ind_to_rem[i];
          int diff = abs(rem1 - rem2);
          cycle_gcd = cycle_gcd == -1 ? diff : gcd(cycle_gcd, diff);
        }
      }

      reset_dsu();
    }
  }

  vector<int> ans;

  for (int i = 1; i <= n; i++) {
    if (cycle_gcd == -1 or cycle_gcd % i == 0) {
      ans.push_back(i);
    }
  }

  cout << ans.size() << "\n";
  for (int i = 0; i < ans.size(); i++) {
    if (i) cout << " ";
    cout << ans[i];
  }
  cout << "\n";

  return 0;
}