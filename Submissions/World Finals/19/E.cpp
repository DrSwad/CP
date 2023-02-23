#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, m;
  cin >> n >> m;

  vector<int> d(n, 0);
  vector<vector<int>> e(n);

  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    e[u].push_back(v);
    e[v].push_back(u);
    d[u]++, d[v]++;
  }

  set<pair<int, int>> ans_candidates;
  vector<int> visited_from(n, 0);
  vector<set<int>> can_be_ans_from(n);
  set<pair<int, int>> can_not_be_ans;

  for (int from = 0; from < n; from++) {
    for (int to : e[from]) {
      can_be_ans_from[from].insert(to);
    }
  }

  function<void(int, int)> new_ans_pair = [&](int at, int from) {
    if (ans_candidates.count(make_pair(from, at))) return;
    ans_candidates.insert(make_pair(from, at));
    // cerr << at << " " << from << "\n";

    visited_from[from]++;
    if (visited_from[from] >= d[from] - 2) {
      for (int nxt : e[from]) {
        int rest = visited_from[from] - ans_candidates.count(make_pair(from, nxt));
        if (rest == d[from] - 1) {
          // cerr << "Found nxt: " << nxt << "\n";
          new_ans_pair(from, nxt);
          while (!can_be_ans_from[from].empty()) {
            if (*can_be_ans_from[from].begin() != nxt) {
              int to = *can_be_ans_from[from].begin();
              can_be_ans_from[from].erase(to);
              can_not_be_ans.insert(make_pair(from, to));
            }
            else if (*prev(can_be_ans_from[from].end()) != nxt) {
              int to = *prev(can_be_ans_from[from].end());
              can_be_ans_from[from].erase(to);
              can_not_be_ans.insert(make_pair(from, to));
            }
            else break;
          }
        }
      }
    }
  };

  for (int at = 0; at < n; at++) {
    if (d[at] == 1) {
      new_ans_pair(at, e[at][0]);
    }
  }

  // cerr << "Can not be ans:\n";
  // for (auto [from, to] : can_not_be_ans) {
  //   cerr << from << " " << to << "\n";
  // }

  vector<pair<int, int>> ans;
  for (auto [from, to] : ans_candidates) {
    if (!can_not_be_ans.count(make_pair(from, to))) {
      ans.emplace_back(from, to);
    }
  }
  cout << ans.size() << "\n";
  for (auto [from, to] : ans) {
    cout << from + 1 << " " << to + 1 << "\n";
  }

  return 0;
}