#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> g; // [0..n) -> [0..m)
vector<int> mtn, mtm;
vector<char> used;

bool try_kuhn(int v) {
  if (used[v]) return false;
  used[v] = true;
  for (int to : g[v]) {
    if (mtm[to] == -1 or try_kuhn(mtm[to])) {
      mtm[to] = v;
      mtn[v] = to;
      return true;
    }
  }
  return false;
}

void match() {
  mtn.assign(n, -1);
  mtm.assign(m, -1);

  vector<int> order(n);
  iota(order.begin(), order.end(), 0);
  // modify order if custom order needed

  used.assign(n, false);
  for (int v : order) {
    if (mtn[v] == -1 and try_kuhn(v)) {
      used.assign(n, false);
    }
  }
}

int main() {
  cin >> n >> m;

  vector<vector<int>> a(n + 1, vector<int>(m + 1, 0));
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    for (int j = 0; j < m; j++) {
      a[i][j] = s[j] == 'B';
    }
  }

  vector<vector<int>> b(n, vector<int>(m));
  g.resize(n);
  int ans = 0;
  for (int i = n - 1; i >= 0; i--) {
    for (int j = m - 1; j >= 0; j--) {
      b[i][j] = (a[i][j] + a[i][j + 1] + a[i + 1][j] + a[i + 1][j + 1]) % 2;
      ans += b[i][j];
      if (i < n - 1 and j < m - 1) {
        if (b[i][j] and b[i][m - 1] and b[n - 1][j]) {
          g[i].push_back(j);
        }
      }
    }
  }

  match();

  int matches = 0;
  for (int i = 0; i < n; i++) matches += mtn[i] != -1;

  ans -= matches;
  if (matches % 2 == 1) ans += b[n - 1][m - 1] ? -1 : 1;

  cout << ans << "\n";

  return 0;
}