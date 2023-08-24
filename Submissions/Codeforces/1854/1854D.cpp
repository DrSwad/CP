#include <bits/stdc++.h>
using namespace std;

const int k = 1e8;

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

void brute_answer(int n, vector<int> cycle) {
  vector<int> ans;
  for (int i = 0; i < n; i++) {
    if (query(i, k, cycle)) ans.push_back(i);
  }
  answer(ans);
}

int brute_query(int n, int from, int steps) {
  vector<int> st(n);
  iota(st.begin(), st.end(), 0);

  while (st.size() > 1) {
    int sz = st.size();
    vector<int> st1, st2;
    for (int i = 0; i < sz / 2; i++) st1.push_back(st[i]);
    for (int i = sz / 2; i < sz; i++) st2.push_back(st[i]);
    if (query(from, steps, st1)) swap(st, st1);
    else swap(st, st2);
  }

  return st[0];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> cycle;
  cycle.push_back(brute_query(n, 0, k));
  cycle.push_back(brute_query(n, 0, k + 1));
  cycle.push_back(brute_query(n, 0, k + 2));

  if (cycle[0] == cycle[1] or cycle[1] == cycle[2] or cycle[2] == cycle[0]) {
    sort(cycle.begin(), cycle.end());
    cycle.resize(unique(cycle.begin(), cycle.end()) - cycle.begin());
    brute_answer(n, cycle);
  }

  while (true) {
    int nxt = brute_query(n, cycle.back(), 3);
    if (find(cycle.begin(), cycle.end(), nxt) != cycle.end()) break;
    cycle.push_back(nxt);
  }

  vector<int> state(n, -1);
  for (int i : cycle) state[i] = 1;

  for (int i = 0; i < n; i++) {
    if (state[i] != -1) continue;
    int got0 = brute_query(n, 0, k);
    cycle.push_back(brute_query(n, 0, k + 1));
    cycle.push_back(brute_query(n, 0, k + 2));
  }

  return 0;
}