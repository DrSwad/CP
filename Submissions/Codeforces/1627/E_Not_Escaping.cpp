#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int rows, cols, lads;
  cin >> rows >> cols >> lads;

  vector<int> step_cost(rows);
  for (int &i : step_cost) cin >> i;

  vector<tuple<pair<int, int>, pair<int, int>, int>> ladders(lads);
  vector<vector<int>> ladders_from(rows), ladders_to(rows);
  {
    int at_ladder = 0;
    for (auto &ladder : ladders) {
      auto & [from, to, h] = ladder;
      auto & [fromx, fromy] = from;
      auto & [tox, toy] = to;

      cin >> fromx >> fromy >> tox >> toy >> h;
      fromx--, fromy--, tox--, toy--;

      ladders_from[fromx].push_back(at_ladder);
      ladders_to[tox].push_back(at_ladder);

      at_ladder++;
    }
  }

  vector<ll> dp(lads + 2, LLONG_MAX);
  vector<bool> reachable(lads + 2, false);

  ladders.push_back({{-1, -1}, {0, 0}, 0});
  ladders_to[0].push_back(lads);
  dp[lads] = 0;
  reachable[lads] = true;
  lads++;

  ladders.push_back({{rows - 1, cols - 1}, {-1, -1}, 0});
  ladders_from[rows - 1].push_back(lads);
  lads++;

  auto solve_level = [&](int at_level) {
    bool found = false;
    ll mn = LLONG_MAX;

    int to_i = 0, from_i;
    for (from_i = 0; from_i < ladders_from[at_level].size(); from_i++) {
      int from_id = ladders_from[at_level][from_i];
      int from_y = get<0>(ladders[from_id]).second;

      while (to_i < ladders_to[at_level].size()) {
        int to_id = ladders_to[at_level][to_i];
        int to_y = get<1>(ladders[to_id]).second;

        if (to_y <= from_y) {
          if (reachable[to_id]) {
            found = true;
            mn = min(mn, dp[to_id] - (ll)step_cost[at_level] * to_y);
          }
          to_i++;
        }
        else break;
      }

      if (found) {
        reachable[from_id] = true;
        dp[from_id] = min(dp[from_id], mn + (ll)step_cost[at_level] * from_y - get<2>(ladders[from_id]));
      }
    }
  };

  for (int at_level = 0; at_level < rows; at_level++) {
    sort(
      ladders_from[at_level].begin(),
      ladders_from[at_level].end(),
      [&](int i1, int i2) {
      auto [from1, to1, h1] = ladders[i1];
      auto [fromx1, fromy1] = from1;
      auto [from2, to2, h2] = ladders[i2];
      auto [fromx2, fromy2] = from2;
      return fromy1 < fromy2;
    }
      );
    sort(
      ladders_to[at_level].begin(),
      ladders_to[at_level].end(),
      [&](int i1, int i2) {
      auto [from1, to1, h1] = ladders[i1];
      auto [tox1, toy1] = to1;
      auto [from2, to2, h2] = ladders[i2];
      auto [tox2, toy2] = to2;
      return toy1 < toy2;
    }
      );

    // DB();
    // debug(at_level);
    // debug(ladders_from[at_level]);
    // debug(ladders_to[at_level]);

    solve_level(at_level);

    // for (int id : ladders_from[at_level]) {
    //   cerr << id << " " << reachable[id] << " " << dp[id] << endl;
    // }

    reverse(ladders_from[at_level].begin(), ladders_from[at_level].end());
    for (int id : ladders_from[at_level]) {
      get<0>(ladders[id]).second = cols - 1 - get<0>(ladders[id]).second;
    }
    reverse(ladders_to[at_level].begin(), ladders_to[at_level].end());
    for (int id : ladders_to[at_level]) {
      get<1>(ladders[id]).second = cols - 1 - get<1>(ladders[id]).second;
    }

    solve_level(at_level);

    // for (int id : ladders_from[at_level]) {
    //   cerr << id << " " << reachable[id] << " " << dp[id] << endl;
    // }
  }

  if (!reachable[lads - 1]) cout << "NO ESCAPE\n";
  else cout << dp[lads - 1] << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}