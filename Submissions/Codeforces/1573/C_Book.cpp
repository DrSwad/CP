#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int n;
vector<int> e[N];
int vis[N];
bool cycle;
int h[N];

void reset() {
  cycle = false;

  for (int i = 1; i <= n; i++) {
    vis[i] = 0;
    h[i] = 0;
    e[i].clear();
  }
}

void dfs(int at) {
  if (vis[at] == 1) {
    cycle = true;
    return;
  }
  if (vis[at] == 2) return;

  vis[at] = 1;
  h[at] = 1;

  for (int to : e[at]) {
    dfs(to);
    h[at] = max(h[at], h[to] + (to > at));
  }

  vis[at] = 2;
}

void test_case() {
  cin >> n;

  for (int i = 1; i <= n; i++) {
    int k;
    cin >> k;

    while (k--) {
      int j;
      cin >> j;

      e[i].push_back(j);
    }
  }

  for (int i = 1; i <= n; i++) {
    if (!vis[i]) {
      dfs(i);
    }
  }

  if (cycle) cout << -1 << "\n";
  else cout << *max_element(h + 1, h + n + 1) << "\n";

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