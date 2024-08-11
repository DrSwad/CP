#include <bits/stdc++.h>
using namespace std;

const int N = 20;
const int inf = 1e9;

int tot_cities;
int cost[N][N];
map<pair<int, vector<bool>>, int> dp;

// if I start from `0` and I need to finish at the node `at`,
// while visiting all the nodes indicated by `vis`, the
// DP calculates the minimum cost I need to travel
int DP(int at, vector<bool> vis) {
  pair<int, vector<bool>> state = {at, vis};
  if (dp.find(state) != dp.end()) return dp[state];
  dp[state] = inf;

  // since we began at `0`, `vis[0]` must be `true` in a valid state
  if (vis[0] != true) return inf;

  // iterate over the city `from`, which came immediate before `at` in the journey
  vis[at] = false;
  for (int from = 0; from < tot_cities; from++) {
    if (vis[from]) {
      dp[state] = min(dp[state], cost[from][at] + DP(from, vis));
    }
  }

  return dp[state];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  while (t--) {
    cin >> tot_cities;

    for (int from = 0; from < tot_cities; from++) {
      for (int to = 0; to < tot_cities; to++) {
        cin >> cost[from][to];
      }
    }

    dp.clear();

    // at the start, only city `0` visited and we're standing there
    int source = 0;
    vector<bool> start_vis(tot_cities, false);
    start_vis[source] = true;
    dp[make_pair(source, start_vis)] = 0;

    // at the end, all the cities must be visited
    vector<bool> end_vis(tot_cities, true);

    // iterate over which city was last visited before completing the cycle by returning back to city `0`
    int ans = INT_MAX;
    for (int last_city = 0; last_city < tot_cities; last_city++) {
      ans = min(ans, DP(last_city, end_vis) + cost[last_city][0]);
    }

    cout << ans << "\n";
  }

  return 0;
}