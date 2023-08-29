#include <bits/stdc++.h>
using namespace std;

const int k_inf = 1e8;
const int min_cycle_len = 31 * 4;

bool query(int from, int steps, vector<int> st) {
  cout << "? " << from + 1 << " " << steps << " " << st.size();
  for (int i : st) cout << " " << i + 1;
  cout << endl;

  int res;
  cin >> res;
  return res;
}

void answer(vector<int> ans) {
  cout << "! " << ans.size();
  for (int i : ans) cout << " " << i + 1;
  cout << endl;
  exit(EXIT_SUCCESS);
}

// Costs 9 queries
int brute_query(int n, int from, int steps) {
  vector<int> st(n);
  iota(st.begin(), st.end(), 0);

  while (st.size() > 1) {
    int sz = st.size();
    vector<int> st1(st.begin(), st.begin() + sz / 2);
    vector<int> st2(st.begin() + sz / 2, st.end());
    if (query(from, steps, st1)) swap(st, st1);
    else swap(st, st2);
  }

  return st[0];
}

void brute_answer(int n, int cycle_start) {
  vector<int> cycle;
  cycle.push_back(cycle_start);
  do {
    cycle.push_back(brute_query(n, cycle.back(), 1));
  } while (cycle.back() != cycle_start);
  cycle.pop_back();

  vector<int> ans = cycle;
  ans.push_back(0);
  for (int i = 1; i < n; i++) {
    if (find(cycle.begin(), cycle.end(), i) == cycle.end() and query(i, k_inf, cycle)) ans.push_back(i);
  }
  sort(ans.begin(), ans.end());
  ans.resize(unique(ans.begin(), ans.end()) - ans.begin());
  answer(ans);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> cycle;
  int cycle_start = brute_query(n, 0, k_inf);
  cycle.push_back(cycle_start);
  cycle.push_back(brute_query(n, cycle_start, 1));
  cycle.push_back(brute_query(n, cycle_start, 2));
  cycle.push_back(brute_query(n, cycle_start, 3));

  if (cycle[1] == cycle_start or cycle[2] == cycle_start or cycle[3] == cycle_start) {
    brute_answer(n, cycle_start);
  }

  int cycle_len = 0;
  int at = cycle_start;
  while (true) {
    at = brute_query(n, at, 4);
    cycle_len += 4;
    bool stop = false;
    for (int rem = 0; rem < 4; rem++) {
      if (cycle[rem] == at) {
        cycle_len -= rem;
        stop = true;
        break;
      }
    }
    if (stop) break;
    cycle.push_back(at);
  }

  if (cycle_len < min_cycle_len) brute_answer(n, cycle_start);

  int k[4];
  k[0] = (k_inf - k_inf % cycle_len);
  for (int i = 1; i < 4; i++) {
    k[i] = k[i - 1] + 1;
  }

  vector<int> ans = cycle;
  ans.push_back(0);
  for (int i = 1; i < n; i++) {
    if (find(cycle.begin(), cycle.end(), i) != cycle.end()) continue;
    for (int rem = 1; rem <= 4; rem++) {
      if (query(i, k[rem % 4], cycle)) {
        ans.push_back(i);
        break;
      }
    }
  }
  sort(ans.begin(), ans.end());
  ans.resize(unique(ans.begin(), ans.end()) - ans.begin());
  answer(ans);

  return 0;
}