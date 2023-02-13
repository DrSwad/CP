#include <bits/stdc++.h>
using namespace std;

const int N = 8e5 + 5;

int n;
vector<int> g[N];
int col[N];
map<int, int> *cnt[N];
int tot_col;
map<int, int> col_freq;
int sz[N];
int ans;

void reset() {
  for (int i = 1; i <= n; i++) {
    g[i].clear();
    (*cnt[i]).clear();
    sz[i] = 0;
    col_freq.clear();
    ans = 0;
  }
}

void dfs1(int v, int p) {
  sz[v] = 1;
  col_freq[col[v]]++;
  for (auto u : g[v]) {
    if (u != p) {
      dfs1(u, v);
      sz[v] += sz[u];
    }
  }
}

void dfs2(int v, int p) {
  int mx = -1, bigChild = -1;
  for (auto u : g[v]) {
    if (u != p) {
      if (sz[u] > mx) mx = sz[u], bigChild = u;
    }
  }

  for (auto u : g[v]) {
    if (u != p and u != bigChild) {
      dfs2(u, v);
      for (auto x : *cnt[u]) col_freq[x.first] += x.second;
    }
  }

  if (bigChild != -1) dfs2(bigChild, v);

  for (auto u : g[v]) {
    if (u != p and u != bigChild) {
      for (auto x : *cnt[u]) {
        col_freq[x.first] -= x.second;
        if (col_freq[x.first] == 0) {
          col_freq.erase(x.first);
        }
      }
    }
  }

  col_freq[col[v]]--;
  if (col_freq[col[v]] == 0) {
    col_freq.erase(col[v]);
  }

  if (bigChild != -1) cnt[v] = cnt[bigChild];
  else cnt[v] = new map<int, int>();

  (*cnt[v])[col[v]]++;

  for (auto u : g[v]) {
    if (u != p && u != bigChild) {
      for (auto x : *cnt[u]) (*cnt[v])[x.first] += x.second;
    }
  }

  if (p and (*cnt[v]).size() + col_freq.size() == tot_col) ans++;

  // debug(v, *cnt[v], col_freq, (*cnt[v]).size(), col_freq.size(), tot_col);
}

void test_case() {
  cin >> n;
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  for (int i = 1; i <= n; i++) {
    cin >> col[i];
  }

  dfs1(1, 0);
  tot_col = col_freq.size();
  dfs2(1, 0);

  cout << ans << "\n";

  reset();
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}