#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int n, l, r;
set<int> rem;
int p[N], sz[N];

int root(int v) {
  return p[v] == v ? v : (p[v] = root(p[v]));
}

void merge(int x, int y) {
  x = root(x);
  y = root(y);
  if (x == y) return;
  if (sz[x] > sz[y]) swap(x, y);
  p[y] = x;
  sz[x] += sz[y];
}

void dfs(int at) {
  rem.erase(at);

  auto it = rem.lower_bound(at + l);
  while (it != rem.end() and * it <= at + r) {
    merge(at, *it);
    dfs(*it);
    it = rem.lower_bound(at + l);
  }

  it = rem.lower_bound(at - r);
  while (it != rem.end() and * it <= at - l) {
    merge(at, *it);
    dfs(*it);
    it = rem.lower_bound(at - r);
  }
}

int main() {
  scanf("%d %d %d", &n, &l, &r);
  {
    vector<int> pos(n);
    iota(pos.begin(), pos.end(), 0);
    rem = set<int>(pos.begin(), pos.end());
  }

  iota(p, p + n, 0);
  fill(sz, sz + n, 1);

  for (int i = 0; i < n; i++) {
    if (rem.find(i) != rem.end()) dfs(i);
  }

  string s;
  cin >> s;
  string ans = s;

  vector<vector<int>> comp(n);
  for (int i = 0; i < n; i++) {
    comp[root(i)].push_back(i);
  }

  for (int r = 0; r < n; r++) {
    sort(comp[r].begin(), comp[r].end());
    vector<int> ccomp = comp[r];
    sort(ccomp.begin(), ccomp.end(), [&](int i, int j) {
      return ans[i] < ans[j];
    });
    for (int i = 0; i < comp[r].size(); i++) {
      ans[comp[r][i]] = s[ccomp[i]];
    }
  }

  cout << ans << endl;

  return 0;
}