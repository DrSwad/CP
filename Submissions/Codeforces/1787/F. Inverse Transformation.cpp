#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, k;
  cin >> n >> k;

  vector<int> p(n);
  for (int &i : p) cin >> i, i--;

  auto binExp = [&](long long a, long long e, long long m) {
    if (e == -1) e = m - 2;
    long long ret = 1;
    while (e) {
      if (e & 1) ret = ret * a % m;
      a = a * a % m, e >>= 1;
    }
    return ret;
  };

  auto jump = [&](const vector<int> &cycle, const int k) {
    int sz = cycle.size();
    assert(sz % 2 == 1);
    if (k == 0) return cycle;

    int offset;
    if (31 - __builtin_clz(sz) < k) offset = binExp(2, k, sz);
    else offset = (1 << k) % sz;

    vector<int> p;
    for (int it = 0, at = 0; it < sz; it++) {
      p.push_back(at);
      at = (at + offset) % sz;
    }

    vector<int> prev_cycle(sz);
    for (int i = 0; i < sz; i++) {
      prev_cycle[p[i]] = cycle[i];
    }

    return prev_cycle;
  };

  auto split_into_cycles = [&](const vector<int> &p) {
    vector<vector<int>> cycles;
    vector<bool> vis(n, false);
    for (int i = 0; i < n; i++) {
      if (!vis[i]) {
        cycles.push_back({});
        int at = i;
        do {
          vis[at] = true;
          cycles.back().push_back(at);
          at = p[at];
        } while (at != i);
      }
    }
    return cycles;
  };

  auto construct_perm_from_cycles = [&](const vector<vector<int>> &cycles) {
    vector<int> p(n);
    for (const vector<int> &cycle : cycles) {
      for (int i = 0; i < cycle.size(); i++) {
        int j = i + 1 == cycle.size() ? 0 : i + 1;
        p[cycle[i]] = cycle[j];
      }
    }
    return p;
  };

  function<vector<int>(const vector<int>&, const int)> find_prev = [&](const vector<int> &p, const int k) {
    vector<vector<int>> cycles = split_into_cycles(p);

    vector<vector<int>> cycles_with_len(n + 1);
    for (int i = 0; i < cycles.size(); i++) {
      cycles_with_len[cycles[i].size()].push_back(i);
    }

    vector<vector<int>> prev_cycles;
    for (int len = 1; len <= n; len++) {
      int merge_till;
      int tot_cycles = cycles_with_len[len].size();
      if (tot_cycles == 0) continue;

      if ((31 - __builtin_clz(tot_cycles)) < k) merge_till = 0;
      else {
        merge_till = (tot_cycles / (1 << k)) * (1 << k);
      }

      if (len % 2 == 0 and merge_till < tot_cycles) return vector<int>();

      for (int i = 0; i < merge_till; i += 2) {
        prev_cycles.push_back({});
        for (int j = 0; j < len; j++) {
          prev_cycles.back().push_back(cycles[cycles_with_len[len][i]][j]);
          prev_cycles.back().push_back(cycles[cycles_with_len[len][i + 1]][j]);
        }
      }

      for (int i = merge_till; i < tot_cycles; i++) {
        prev_cycles.push_back(jump(cycles[cycles_with_len[len][i]], 1));
      }
    }

    return construct_perm_from_cycles(prev_cycles);
  };

  while (k) {
    vector<int> prev_p = find_prev(p, k);

    if (prev_p.empty()) {
      cout << "NO\n";
      return;
    }

    k--;
    swap(p, prev_p);

    int mx_k = 31 - __builtin_clz(n);
    if (k > mx_k) {
      int d_k = k - mx_k;

      vector<vector<int>> cycles = split_into_cycles(p);
      vector<vector<int>> new_cycles;
      for (const vector<int>& cycle : cycles) {
        new_cycles.push_back(jump(cycle, d_k));
      }
      p = construct_perm_from_cycles(new_cycles);

      k -= d_k;
    }
  }

  cout << "YES\n";
  for (int i = 0; i < n; i++) {
    if (i) cout << " ";
    cout << p[i] + 1;
  }
  cout << "\n";
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
