#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<vector<vector<bool>>> same(n, vector(n, vector(n, false)));
  vector<vector<int>> matches(n, vector(n, 0));
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      string s;
      cin >> s;
      for (int k = 0; k < n; k++) {
        if (s[k] == '1') {
          same[k][i][j] = same[k][j][i] = true;
          matches[i][j]++, matches[j][i]++;
        }
      }
    }
  }

  vector<pair<int, int>> edges;

  auto remove_sames = [&](int v, vector<int> vs, int add) {
    int sz = vs.size();
    for (int i = 0; i < sz; i++) {
      int v1 = vs[i];
      for (int j = i + 1; j < sz; j++) {
        int v2 = vs[j];
        if (same[v][v1][v2]) {
          matches[v1][v2] += add;
          matches[v2][v1] += add;
        }
      }
    }
  };

  function<int(vector<int>)> solve = [&](vector<int> v) {
    while (true) {
      debug(v);
      debug(matches);
      int sz = v.size();
      int i1, i2;
      for (i1 = 0; i1 < sz; i1++) {
        for (i2 = i1 + 1; i2 < sz; i2++) {
          if (matches[v[i1]][v[i2]] >= 2) break;
        }
        if (i2 < sz) break;
      }

      // bamboo
      if (i1 == sz) {
        vector<int> splits[2];
        splits[0].push_back(v[0]);
        for (int i = 1; i < sz; i++) {
          if (matches[v[0]][v[i]]) {
            splits[0].push_back(v[i]);
          }
          else {
            splits[1].push_back(v[i]);
          }
        }

        if (splits[0].size() < splits[1].size()) swap(splits[0], splits[1]);
        // assert(splits[0].size() - splits[1].size() <= 1);

        for (int i = 0; i < splits[1].size(); i++) {
          edges.push_back({splits[0][i], splits[1][i]});
          if (i + 1 < splits[0].size()) {
            edges.push_back({splits[1][i], splits[0][i + 1]});
          }
        }

        return splits[0][0];
      }

      vector<int> pv, nv;
      int v1 = v[i1], v2 = v[i2];
      for (int i = 0; i < sz; i++) {
        if (i != i1 and i != i2 and same[v[i]][v1][v2]) {
          nv.push_back(v[i]);
        }
        else {
          pv.push_back(v[i]);
        }
      }

      for (int i : pv) remove_sames(i, nv, -1);

      int root = solve(nv);
      debug(root);

      pv.push_back(root);
      nv.erase(find(nv.begin(), nv.end(), root));
      for (int i : nv) remove_sames(i, pv, -1);

      swap(v, pv);
    }
  };

  {
    vector<int> all_vertices(n);
    iota(all_vertices.begin(), all_vertices.end(), 0);
    solve(all_vertices);
  }
  debug(edges);

  if (edges.size() != n - 1) {
    cout << "No\n";
    return;
  }
  vector<vector<int>> e(n);
  for (auto [u, v] : edges) {
    e[u].push_back(v);
    e[v].push_back(u);
  }

  vector<vector<int>> dist(n, vector(n, 0));
  function<void(int, int, int)> dfs = [&](int at, int from, int root) {
    for (int to : e[at]) {
      if (to != from) {
        dist[root][to] = dist[root][at] + 1;
        dfs(to, at, root);
      }
    }
  };

  for (int i = 0; i < n; i++) {
    dist[i][i] = 0;
    dfs(i, -1, i);
  }

  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        if ((dist[k][i] == dist[k][j]) != same[k][i][j]) {
          cout << "No\n";
          return;
        }
      }
    }
  }

  cout << "Yes\n";
  for (auto [u, v] : edges) {
    cout << u + 1 << " " << v + 1 << "\n";
  }
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