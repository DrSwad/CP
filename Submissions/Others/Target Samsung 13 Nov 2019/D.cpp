#include <bits/stdc++.h>
using namespace std;

const int office = 0;
const int home = 1;

int n;
vector<int> x, y;
map<pair<int, vector<bool>>, int> dp;

int dist(int i, int j) {
  return abs(x[i] - x[j]) + abs(y[i] - y[j]);
}

// Assuming I'm at the node `at` currently, and
// the visited nodes are indicted by `vis`, the
// DP calculates how much **more** I need to
// travel to reach `home`
int DP(int at, vector<bool> vis) {
  pair<int, vector<bool>> state = {at, vis};
  if (dp.find(state) != dp.end()) return dp[state];

  // If there is no `false` in `vis`, then everyone is visited
  if (count(vis.begin(), vis.end(), false) == 0) {
    return dist(at, home);
  }

  dp[state] = INT_MAX;

  for (int to = 0; to < n; to++) {
    if (!vis[to]) {
      vis[to] = true;
      dp[state] = min(dp[state], dist(at, to) + DP(to, vis));
      vis[to] = false;
    }
  }

  return dp[state];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  for (int test = 1; test <= 10; test++) {
    cin >> n;
    n += 2;
    x.resize(n), y.resize(n);
    for (int i = 0; i < n; i++) {
      cin >> x[i] >> y[i];
    }

    dp.clear();

    vector<bool> vis(n, false);
    vis[office] = true;
    int ans = DP(office, vis);

    cout << "# " << test << " " << ans << "\n";
  }

  return 0;
}