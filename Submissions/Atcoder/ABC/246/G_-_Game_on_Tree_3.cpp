#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int n;
int a[N];
vector<int> e[N];

int dfs(int at, int from, int low) {
  if (low == 0) return N;

  int ret = 0, mx = 0;
  if (a[at] >= low) ret++;

  for (int to : e[at]) {
    if (to != from) {
      int curr = dfs(to, at, low);
      mx = max(mx, curr);
      ret += curr;
    }
  }

  if (mx > 0) ret--;

  return ret;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;

  for (int i = 2; i <= n; i++) {
    cin >> a[i];
  }

  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    e[u].push_back(v);
    e[v].push_back(u);
  }

  int L = 0, R = 1e9;
  while (L != R) {
    int mid = (L + R + 1) / 2;
    if (dfs(1, 0, mid) >= 1) L = mid;
    else R = mid - 1;
  }

  cout << L << "\n";

  return 0;
}