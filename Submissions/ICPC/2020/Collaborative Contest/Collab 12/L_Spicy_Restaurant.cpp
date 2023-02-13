#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int W = 105;

int n, m, q;
int w[N];
vector<int> e[N];
int st[N], en[N];
pair<int, int> dp[N][W];

void merge(int at, int to, int d, bool allowChild = true) {
  auto [nbest1, nbest2] = dp[to][d - 1];
  auto [cbest1, cbest2] = dp[at][d];

  for (int val : {nbest1, nbest2}) {
    if (val != 0 and (allowChild or st[to] > en[at] or en[to] < st[at])) {
      if (cbest1 == 0 or w[cbest1] >= w[val]) {
        cbest2 = cbest1;
        cbest1 = val;
      }
      else if (cbest2 == 0 or w[cbest2] >= w[val]) {
        cbest2 = val;
      }

      dp[at][d] = {cbest1, cbest2};
    }
  }
}

int T;
void dfs(int at, int from = 0) {
  st[at] = T++;
  fill(begin(dp[at]), end(dp[at]), make_pair(0, 0));
  dp[at][0] = {at, 0};

  for (int to : e[at]) {
    if (to != from) {
      dfs(to, at);
      for (int d = 1; d < W; d++) {
        merge(at, to, d);
      }
    }
  }

  en[at] = T++;
}

void dfs2(int at, int from = 0) {
  if (from) {
    for (int d = 1; d < W; d++) {
      merge(at, from, d, false);
    }
  }

  for (int to : e[at]) {
    if (to != from) {
      dfs2(to, at);
    }
  }
}

int main() {
  int n, m, q;
  scanf("%d %d %d", &n, &m, &q);

  for (int i = 1; i <= n; i++) scanf("%d", &w[i]);

  dfs(1);
  debug() << name(dp[1]);
  dfs2(1);

  while (q--) {
    int p, a;
    scanf("%d %d", &p, &a);

    int d;
    for (d = 1; d < W; d++) {
      if (dp[p][d].first != 0 and dp[p][d].first <= a) break;
    }

    if (d < W) printf("%d\n", d);
    else puts("-1");
  }

  return 0;
}