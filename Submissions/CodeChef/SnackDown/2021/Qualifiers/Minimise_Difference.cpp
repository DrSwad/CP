#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 5;

int n, m;
vector<int> e[N];
vector<int> ans;

void reset() {
  for (int i = 0; i < n; i++) {
    e[i].clear();
  }
}

bool check(int mxd) {
  vector<int> d(n);
  for (int i = 0; i < n; i++) {
    d[i] = e[i].size();
  }

  queue<int> q;
  for (int i = 0; i < n; i++) {
    if (d[i] <= mxd) {
      q.push(i);
    }
  }

  int nc = n;
  vector<int> c(n);

  while (!q.empty()) {
    int u = q.front(); q.pop();
    c[u] = nc--;

    for (int v : e[u]) {
      d[v]--;
      if (d[v] == mxd) {
        q.push(v);
      }
    }
  }

  if (nc == 0) ans = c;

  return nc == 0;
}

void test_case() {
  cin >> n >> m;
  while (m--) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    e[u].push_back(v);
    e[v].push_back(u);
  }

  int L = 0, R = n;
  while (L != R) {
    int m = (L + R) / 2;
    if (check(m)) R = m;
    else L = m + 1;
  }

  cout << L << "\n";
  for (int i = 0; i < n; i++) {
    if (i) cout << " ";
    cout << ans[i];
  }
  cout << "\n";

  reset();
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}