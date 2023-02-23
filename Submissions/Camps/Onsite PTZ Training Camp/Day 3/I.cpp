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

const int N = 2e5 + 5;

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
  int tot = 1;
  for (auto v : order) {
    dp[u] += dp[v] + sub_sum[v] * tot;
    tot += sub_sz[v];
  }
}

ll ans = LLONG_MAX;

ll new_dp[N], new_sub_sum[N], new_sub_sz[N];

ll calc_ans(int at, int from, ll parent_dp = 0) {
  // cerr << "Calc" << endl;
  // debug(at, from, parent_dp);
  ll parent_sub_sz = n - sub_sz[at];
  ll parent_sub_sum = tot_sub_sum - sub_sum[at];
  // debug(parent_sub_sz, parent_sub_sum);

  vector<int> order;

  for (int to : g[at]) {
    if (to == from) {
      if (from != -1) {
        new_dp[from] = parent_dp;
        new_sub_sum[from] = parent_sub_sum;
        new_sub_sz[from] = parent_sub_sz;
        order.push_back(from);
      }
      // debug(to, new_sub_sum[to], new_sub_sz[to]);
    }
    else {
      new_dp[to] = dp[to];
      new_sub_sum[to] = sub_sum[to];
      new_sub_sz[to] = sub_sz[to];
      order.push_back(to);
      // debug(to, new_sub_sum[to], new_sub_sz[to]);
    }
  }

  sort(
    order.begin(),
    order.end(),
    [&](int i, int j) {
    return new_sub_sum[j] * new_sub_sz[i] < new_sub_sum[i] * new_sub_sz[j];
  }
    );
  // debug(order);

  ll curr_ans = A[at];
  int tot = 1;
  for (auto v : order) {
    curr_ans += new_dp[v] + new_sub_sum[v] * tot;
    tot += new_sub_sz[v];
  }

  return curr_ans;
}

void reroot(int at, int from = -1, ll parent_dp = 0) {
  // DB();
  // cerr << "Reroot" << endl;
  // debug(at, from, parent_dp);
  ll curr_dp = calc_ans(at, from, parent_dp);
  // debug(at, from, parent_dp, curr_dp);
  ans = min(ans, curr_dp);

  vector<int> order;
  for (int to : g[at]) {
    if (to != -1) order.push_back(to);
  }

  sort(
    order.begin(),
    order.end(),
    [&](int i, int j) {
    return new_sub_sum[j] * new_sub_sz[i] < new_sub_sum[i] * new_sub_sz[j];
  }
    );
  // debug(order);

  ll tot_sum = 0;
  for (int i : order) {
    tot_sum += new_sub_sum[i];
  }

  vector<ll> suffix_sum, prefix_sz;
  ll pref_sum = 0;
  ll pref_sz = 1;
  for (int i : order) {
    pref_sum += new_sub_sum[i];
    suffix_sum.push_back(tot_sum - pref_sum);
    prefix_sz.push_back(pref_sz);
    pref_sz += new_sub_sz[i];
  }
  // debug(suffix_sum, prefix_sz);

  for (int i = 0; i < order.size(); i++) {
    int to = order[i];
    if (to != from) {
      // debug(curr_dp, to, new_sub_sz[to], suffix_sum[i], new_sub_sum[to], prefix_sz[i] + 1);
      ll ndp = curr_dp - new_sub_sz[to] * suffix_sum[i] - new_sub_sum[to] * prefix_sz[i] - new_dp[to];
      reroot(to, at, ndp);
    }
  }
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