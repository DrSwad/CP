#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m, k;
  cin >> n >> m >> k;

  function<int(int, int, int)> diag_id =
    [&](int diag_type, int x, int y) {
      if (diag_type == 0) return x + y;
      else return y - x + n;
    };

  function<bool(int, int)> is_inside =
    [&](int x, int y) {
      return 0 <= x and x <= n and 0 <= y and y <= m;
    };

  const int dx[] = {+1, +1, -1, -1};
  const int dy[] = {+1, -1, +1, -1};
  function<pair<int, int>(int, int, int)> travel =
    [&](int diag_type, int at_x, int at_y) {
      int at_diag_id = diag_id(diag_type, at_x, at_y);
      int dir;
      bool found = false;

      for (dir = 0; dir < 4; dir++) {
        int to_x = at_x + dx[dir];
        int to_y = at_y + dy[dir];
        int to_diag_id = diag_id(diag_type, to_x, to_y);
        if (is_inside(to_x, to_y) and at_diag_id == to_diag_id) {
          found = true;
          break;
        }
      }
      assert(found);

      int L = 1, R = N + 1;
      while (R - L > 1) {
        int mid = (R + L) / 2;
        int to_x = at_x + dx[dir] * mid;
        int to_y = at_y + dy[dir] * mid;
        int to_diag_id = diag_id(diag_type, to_x, to_y);
        if (is_inside(to_x, to_y) and at_diag_id == to_diag_id) {
          L = mid;
        }
        else {
          R = mid;
        }
      }

      int to_x = at_x + dx[dir] * L, to_y = at_y + dy[dir] * L;
      return pair<int, int>{to_x, to_y};
    };

  vector<pair<int, int>> points(k);
  vector diags(2, vector(n + m + 1, set<int>()));
  for (int i = 0; i < k; i++) {
    auto & [x, y] = points[i];
    cin >> x >> y;

    for (int diag_type = 0; diag_type < 2; diag_type++) {
      diags[diag_type][diag_id(diag_type, x, y)].insert(i);
    }
  }

  map<pair<int, int>, bool> visited;
  vector<pair<int, int>> banned{{0, 0}, {n, 0}, {0, m}, {n, m}};
  int at_x = 0, at_y = 0;
  long long time_elapsed = 0;
  int diag_type = 1;
  vector<long long> ans(k, -1);

  do {
    visited[make_pair(at_x, at_y)] = true;

    vector<int> found;
    for (int id : diags[diag_type][diag_id(diag_type, at_x, at_y)]) {
      found.push_back(id);
    }

    for (int id : found) {
      auto [x, y] = points[id];
      ans[id] = time_elapsed + abs(x - at_x);
      for (int diag_type = 0; diag_type < 2; diag_type++) {
        diags[diag_type][diag_id(diag_type, x, y)].erase(id);
      }
    }

    auto [to_x, to_y] = travel(diag_type, at_x, at_y);
    diag_type ^= 1;
    time_elapsed += abs(to_x - at_x);
    at_x = to_x;
    at_y = to_y;
  } while (visited.find(make_pair(at_x, at_y)) == visited.end() and find(banned.begin(), banned.end(), make_pair(at_x, at_y)) == banned.end());

  for (long long i : ans) cout << i << "\n";

  return 0;
}