#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 5;
const int MOD = 1e9 + 7;

int n, x;
vector<int> e[N];

long long dfs(int at, int from = 0) {
  vector<long long> children;
  for (int to : e[at]) {
    if (to != from) {
      children.push_back(dfs(to, at));
    }
  }

  sort(children.begin(), children.end(), greater<long long>());

  long long ret = 1;
  for (int i = 0; i < children.size(); i++) {
    ret += children[i] * (i + 1);
  }

  return ret;
}

int main() {
  int t;
  cin >> t;

  while (t--) {
    scanf("%d %d", &n, &x);

    for (int i = 1; i < n; i++) {
      int u, v;
      scanf("%d %d", &u, &v);
      e[u].push_back(v);
      e[v].push_back(u);
    }

    printf("%d\n", dfs(1) % MOD * x % MOD);

    for (int i = 1; i <= n; i++) e[i].clear();
  }

  return 0;
}