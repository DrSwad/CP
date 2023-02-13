#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int MOD = 1e9 + 7;

int n;
int p[N];
vector<int> e[N];
int a[N];
int dp[N][2];

void reset() {
  for (int i = 0; i < n; i++) {
    e[i].clear();
  }
}

inline void add(int &var, int val) {
  var += val;
  if (var >= MOD) var -= MOD;
}

inline int mul(int val1, int val2) {
  return (long long)val1 * val2 % MOD;
}

void dfs(int at) {
  debug() << name(at);
  dp[at][0] = dp[at][1] = 1;

  for (int to : e[at]) {
    dfs(to);
    int dir = a[to] > a[at];
    add(dp[at][dir], dp[to][dir]);
  }

  debug() << name(at) name(dp[at][0]) name(dp[at][1]);
}

void test_case() {
  scanf("%d", &n);
  for (int i = 2; i <= n; i++) {
    scanf("%d", &p[i]);
    e[p[i]].push_back(i);
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }

  dfs(1);

  int ans = 0;
  for (int i = 1; i <= n; i++) {
    int curr = mul(dp[i][0], dp[i][1]);
    add(curr, MOD - 1);
    add(ans, curr);
  }

  printf("%d\n", ans);

  reset();
}

int main() {
  int t;
  cin >> t;

  while (t--) {
    test_case();
  }

  return 0;
}