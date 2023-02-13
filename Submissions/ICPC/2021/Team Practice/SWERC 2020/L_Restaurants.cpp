#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<int> r_cap(m);
  for (int &i : r_cap) cin >> i;

  vector<vector<int>> p_opt(n);
  cin.ignore();
  for (auto &opts : p_opt) {
    string line;
    getline(cin, line);
    stringstream ss(line);
    int opt;
    while (ss >> opt) opts.push_back(opt - 1);
  }

  vector<vector<int>> r_opt(m);
  vector<unordered_map<int, int>> r_pref(m);
  for (int r = 0; r < m; r++) {
    string line;
    getline(cin, line);
    stringstream ss(line);
    int p;
    while (ss >> p) {
      r_opt[r].push_back(p - 1);
      r_pref[r][p - 1] = r_pref[r].size();
    }
  }

  vector<set<int>> r_sorted_pref(m);
  vector<int> r_cnt(m, 0);
  vector<int> p_picked(n, -1);

  function<void(int)> assign_r = [&](int p) {
    int &at = p_picked[p];
    auto &opts = p_opt[p];
    if (at >= (int)opts.size()) return;
    at++;

    while (at < (int)opts.size()) {
      int r = opts[at];
      if (r_cnt[r] == r_cap[r] and * r_sorted_pref[r].rbegin() < r_pref[r][p]) at++;
      else break;
    }

    if (at < (int)opts.size()) {
      int r = opts[at];
      if (r_cnt[r] < r_cap[r]) {
        r_cnt[r]++;
        r_sorted_pref[r].insert(r_pref[r][p]);
      }
      else {
        int np = r_opt[r][*r_sorted_pref[r].rbegin()];
        r_sorted_pref[r].erase(prev(r_sorted_pref[r].end()));
        r_sorted_pref[r].insert(r_pref[r][p]);
        assign_r(np);
      }
    }
  };

  for (int p = 0; p < n; p++) {
    assign_r(p);
  }

  for (int p = 0; p < n; p++) {
    if (p_picked[p] < p_opt[p].size()) {
      cout << (p + 1) << "\n";
    }
  }

  return 0;
}