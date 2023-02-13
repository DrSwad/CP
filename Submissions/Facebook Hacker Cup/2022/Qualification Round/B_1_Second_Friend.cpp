#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, m;
  cin >> n >> m;
  int tot = n * m;

  string grid;
  {
    string row;
    for (int i = 0; i < n; i++) {
      cin >> row;
      grid += row;
    }
  }

  vector<int> d(tot);
  for (int i = 0; i < tot; i++) {
    if (i - m >= 0) d[i]++;
    if (i + m < tot) d[i]++;
    if (i - 1 >= 0 and (i - 1) % m != m - 1) d[i]++;
    if (i + 1 < tot and (i + 1) % m != 0) d[i]++;
  }

  queue<int> q;
  for (int i = 0; i < tot; i++) {
    if (grid[i] == '#') q.push(i);
    else if (d[i] <= 1) q.push(i);
  }

  vector<bool> vis(tot, true);
  {
    auto handle_adj = [&](int j) {
      d[j]--;
      if (d[j] <= 1 and vis[j]) {
        vis[j] = false;
        q.push(j);
      }
    };
    while (!q.empty()) {
      int i = q.front(); q.pop();
      vis[i] = false;
      if (i - m >= 0) handle_adj(i - m);
      if (i + m < tot) handle_adj(i + m);
      if (i - 1 >= 0 and (i - 1) % m != m - 1) handle_adj(i - 1);
      if (i + 1 < tot and (i + 1) % m != 0) handle_adj(i + 1);
    }
  }

  for (int i = 0; i < tot; i++) {
    if (grid[i] == '^' and !vis[i]) {
      cout << "Impossible\n";
      return;
    }
  }

  cout << "Possible\n";
  for (int i = 0; i < tot; i++) {
    if (vis[i]) cout << '^';
    else if (grid[i] == '#') cout << '#';
    else cout << '.';
    if (i % m == m - 1) cout << '\n';
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}