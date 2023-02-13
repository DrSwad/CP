#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;

int n, d;
int a[N];
int len[N];
int vis[N];

void reset() {
  for (int i = 0; i < n; i++) {
    vis[i] = 0;
    len[i] = 0;
  }
}

int dfs(int at) {
  if (vis[at] == 1) return 1;
  if (vis[at] == 2) return len[at];
  vis[at] = 1;
  if (a[at] == 0) len[at] = 0;
  else len[at] = 1 + dfs((at + d) % n);
  vis[at] = 2;
  return len[at];
}

void test_case() {
  cin >> n >> d;
  for (int i = 0; i < n; i++) cin >> a[i];

  int ans = 0;
  for (int i = 0; i < n; i++) {
    if (!vis[i]) ans = max(ans, dfs(i));
  }

  int c = n / gcd(n, d);
  cout << (ans >= c ? -1 : ans) << "\n";

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