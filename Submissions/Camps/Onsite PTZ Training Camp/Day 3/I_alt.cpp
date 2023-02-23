/*
   Output:
   30
 */
/*
   Log:
   {
   Reroot
   [at, from, parent_dp]: 1 -1 0
   Calc
   [at, from, parent_dp]: 1 -1 0
   [parent_sub_sz, parent_sub_sum]: 0 0
   [to, new_sub_sum[to], new_sub_sz[to]]: 2 4 1
   [to, new_sub_sum[to], new_sub_sz[to]]: 3 6 3
   [order]: {2, 3}
   [at, from, parent_dp, curr_dp]: 1 -1 0 35
   [order]: {2, 3}
   [suffix_sum, prefix_sz]: {6, 0} {2, 5}
   {
   Reroot
    [at, from, parent_dp]: 2 1 21
   Calc
    [at, from, parent_dp]: 2 1 21
    [parent_sub_sz, parent_sub_sum]: 4 11
    [to, new_sub_sum[to], new_sub_sz[to]]: 1 11 4
    [order]: {1}
    [at, from, parent_dp, curr_dp]: 2 1 21 36
    [order]: {1}
    [suffix_sum, prefix_sz]: {0} {5}
   }
   {
   Reroot
    [at, from, parent_dp]: 3 1 5
   Calc
    [at, from, parent_dp]: 3 1 5
    [parent_sub_sz, parent_sub_sum]: 2 9
    [to, new_sub_sum[to], new_sub_sz[to]]: 1 9 2
    [to, new_sub_sum[to], new_sub_sz[to]]: 4 2 1
    [to, new_sub_sum[to], new_sub_sz[to]]: 5 1 1
    [order]: {1, 4, 5}
    [at, from, parent_dp, curr_dp]: 3 1 5 30
    [order]: {1, 4, 5}
    [suffix_sum, prefix_sz]: {3, 1, 0} {3, 4, 5}
    {
   Reroot
      [at, from, parent_dp]: 4 3 21
   Calc
      [at, from, parent_dp]: 4 3 21
      [parent_sub_sz, parent_sub_sum]: 4 13
      [to, new_sub_sum[to], new_sub_sz[to]]: 3 13 4
      [order]: {3}
      [at, from, parent_dp, curr_dp]: 4 3 21 36
      [order]: {3}
      [suffix_sum, prefix_sz]: {0} {5}
    }
    {
   Reroot
      [at, from, parent_dp]: 5 3 25
   Calc
      [at, from, parent_dp]: 5 3 25
      [parent_sub_sz, parent_sub_sum]: 4 14
      [to, new_sub_sum[to], new_sub_sz[to]]: 3 14 4
      [order]: {3}
      [at, from, parent_dp, curr_dp]: 5 3 25 40
      [order]: {3}
      [suffix_sum, prefix_sz]: {0} {5}
    }
   }
   }
 */

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 2e2 + 5;

int n;
vector<int> g[N];
ll A[N];
ll sub_sz[N], sub_sum[N];
ll tot_sub_sum;
ll dp[N];

void dfs(int u, int p = -1) {
  sub_sum[u] = A[u];
  sub_sz[u] = 1;
  tot_sub_sum += A[u];

  vector<int> order;
  for (auto v : g[u]) {
    if (v ^ p) {
      dfs(v, u);
      order.push_back(v);
      sub_sz[u] += sub_sz[v];
      sub_sum[u] += sub_sum[v];
    }
  }

  sort(
    order.begin(),
    order.end(),
    [&](int a, int b) {
    return sub_sum[b] *  sub_sz[a] < sub_sum[a] * sub_sz[b];
  }
    );

  dp[u] = A[u];
  ll tot = 1;
  for (auto v : order) {
    dp[u] += dp[v] + sub_sum[v] * tot;
    tot += sub_sz[v];
  }
}

ll ans = LLONG_MAX;

void reroot(int u, int p = -1, ll p_dp = 0, ll p_sub_sum = 0, ll p_sub_sz = 0) {

  // cout << "IN " << u << endl;

  int _u_dp = dp[u];
  int _u_sub_sum = sub_sum[u];
  int _u_sub_sz = sub_sz[u];

  if (p != -1) {
    sub_sum[p] -= sub_sum[u];
    sub_sz[p] -= sub_sz[u];

    vector<int> order;
    for (auto v : g[p]) {
      if (v ^ u) {
        order.push_back(v);
      }
    }

    sort(
      order.begin(),
      order.end(),
      [&](int a, int b) {
      return sub_sum[b] *  sub_sz[a] < sub_sum[a] * sub_sz[b];
    }
      );

    ll tot = 1;
    dp[p] = A[p];
    for (auto v : order) {
      dp[p] += dp[v] + tot * sub_sum[v];
      tot += sub_sz[v];
    }
  }

  sub_sum[u] = tot_sub_sum;
  sub_sz[u] = n;

  vector<int> order;
  for (auto v : g[u]) {
    order.push_back(v);
  }

  sort(
    order.begin(),
    order.end(),
    [&](int a, int b) {
    return sub_sum[b] *  sub_sz[a] < sub_sum[a] * sub_sz[b];
  }
    );

  ll ans_dp = A[u];
  ll tot = 1;
  for (auto v : order) {
    // cout << v << ' ' << dp[v] << endl;
    ans_dp += dp[v] + tot * sub_sum[v];
    tot += sub_sz[v];
  }
  ans = min(ans, ans_dp);

  swap(ans_dp, dp[u]);

  debug(u, dp[u]);

  // cout << u << ' ' << dp[u] << endl;

  for (auto v : g[u]) {
    if (v ^ p) {
      reroot(v, u, dp[u], sub_sum[u], sub_sz[u]);
    }
  }

  if (p != -1) {
    dp[p] = p_dp;
    sub_sum[p] = p_sub_sum;
    sub_sz[p] = p_sub_sz;
  }

  dp[u] = ans_dp;
  sub_sum[u] = _u_sub_sum;
  sub_sz[u] = _u_sub_sz;
}

int main() {
  cin >> n;

  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  for (int i = 1; i <= n; i++) cin >> A[i];

  dfs(1);
  reroot(1);

  cout << ans << endl;
}