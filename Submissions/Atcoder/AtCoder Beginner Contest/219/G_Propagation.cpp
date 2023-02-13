#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
const int MXE = 450;

int n, m, q;
vector<int> e[N], be[N];
pair<int, int> c[N];
pair<int, int> up[N];
bool is_big[N];

int color(int v) {
  if (is_big[v]) return c[v].first;

  for (int u : e[v]) {
    if (is_big[u]) {
      auto [uval, uq] = up[u];
      auto [cval, cq] = c[v];

      if (uq > cq) c[v] = {uval, uq};
    }
  }

  return c[v].first;
}

void test_case() {
  cin >> n >> m >> q;

  while (m--) {
    int u, v;
    cin >> u >> v;
    e[u].push_back(v);
    e[v].push_back(u);
  }

  for (int i = 1; i <= n; i++) {
    c[i] = {i, 0};

    if (e[i].size() > MXE) {
      is_big[i] = true;
      up[i] = {i, 0};

      for (int j : e[i]) {
        if (is_big[j]) {
          be[j].push_back(i);
          be[i].push_back(j);
        }
      }
    }
  }

  for (int qq = 1; qq <= q; qq++) {
    int x;
    cin >> x;

    if (is_big[x]) {
      up[x] = {c[x].first, qq};
      for (int y : be[x]) {
        c[y] = {c[x].first, qq};
      }
    } else {
      int val = color(x);
      for (int y : e[x]) {
        c[y] = {val, qq};
      }
    }
  }

  for (int i = 1; i <= n; i++) {
    if (i > 1) cout << " ";
    cout << color(i);
  }
  cout << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  // cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}