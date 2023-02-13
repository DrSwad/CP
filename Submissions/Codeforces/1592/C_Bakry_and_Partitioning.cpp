#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int n, k;
vector<int> e[N];
int a[N];
int tot;
int sub[N], sub2[N];

void reset() {
  for (int i = 1; i <= n; i++) {
    e[i].clear();
    tot = 0;
  }
}

void dfs(int at, int p = 0) {
  sub[at] = a[at];
  sub2[at] = 0;

  for (int to : e[at]) {
    if (to != p) {
      dfs(to, at);
      sub[at] ^= sub[to];
      sub2[at] += sub2[to];
    }
  }

  if (sub[at] == tot and sub2[at] == 0) sub2[at] = 1;
}

void test_case() {
  cin >> n >> k;

  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    tot ^= a[i];
  }

  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    e[u].push_back(v);
    e[v].push_back(u);
  }

  if (tot == 0) cout << "YES\n";
  else {
    bool ans = false;
    if (k > 2) {
      dfs(1);

      for (int i = 2; i <= n; i++) {
        if (sub[i] == 0 and sub2[i]) {
          ans = true;
          break;
        }
      }

      ans = ans or sub2[1] >= 2;
    }
    cout << (ans ? "YES" : "NO") << "\n";
  }

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