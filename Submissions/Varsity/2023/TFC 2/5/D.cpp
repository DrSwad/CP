#include <bits/stdc++.h>
using namespace std;

/**
 * Description: Calculates a valid assignment to boolean variables a,
 * b, c,... to a 2-SAT problem, so that an expression of the type
 * $(a\|\|b)\&\&(!a\|\|c)\&\&(d\|\|!b)\&\&...$ becomes true, or
 * reports that it is unsatisfiable. Negated variables are represented
 * by bit-inversions (\texttt{\tilde{}x}). Usage: TwoSat ts(number of
 * boolean variables); ts.either(0, \tilde3); // Var 0 is true or var
 * 3 is false ts.set_value(2); // Var 2 is true
 *  ts.at_most_one({0,\tilde1,2}); // <= 1 of vars 0, \tilde1 and 2
 * are true ts.solve(); // Returns true iff it is solvable
 *  ts.values[0..N-1] holds the assigned values to the vars
 * Time: O(N+E), where N is the number of boolean variables, and E is
 * the number of clauses.
 */

struct TwoSat {
  int N;
  vector<vector<int>> gr;
  vector<int> values; // 0 = false, 1 = true

  TwoSat(int n = 0) : N(n), gr(2 * n) {}

  int add_var() { // (optional)
    gr.emplace_back();
    gr.emplace_back();
    return N++;
  }

  void either(int f, int j) {
    f = max(2 * f, -1 - 2 * f);
    j = max(2 * j, -1 - 2 * j);
    gr[f].push_back(j ^ 1);
    gr[j].push_back(f ^ 1);
  }
  void set_value(int x) { either(x, x); }

  void at_most_one(const vector<int> &li) { // (optional)
    if ((int)li.size() <= 1) return;
    int cur = ~li[0];
    for (int i = 2; i < (int)li.size(); i++) {
      int next = add_var();
      either(cur, ~li[i]);
      either(cur, next);
      either(~li[i], next);
      cur = ~next;
    }
    either(cur, ~li[1]);
  }

  vector<int> val, comp, z;
  int time = 0;
  int dfs(int i) {
    int low = val[i] = ++time, x;
    z.push_back(i);
    for (auto &e : gr[i])
      if (!comp[e]) low = min(low, val[e] ?: dfs(e));
    if (low == val[i]) do {
        x = z.back();
        z.pop_back();
        comp[x] = low;
        if (values[x >> 1] == -1) values[x >> 1] = x & 1;
      } while (x != i);
    return val[i] = low;
  }

  bool solve() {
    values.assign(N, -1);
    val.assign(2 * N, 0);
    comp = val;
    for (int i = 0; i < 2 * N; i++) {
      if (!comp[i]) dfs(i);
    }
    for (int i = 0; i < N; i++) {
      if (comp[2 * i] == comp[2 * i + 1]) return 0;
    }
    return 1;
  }
};

int main() {
  // ios::sync_with_stdio(false);
  // cin.tie(nullptr);
  freopen("fragmentation.in", "r", stdin);
  freopen("fragmentation.out", "w", stdout);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<int> vals = a;
  sort(vals.begin(), vals.end());
  vals.resize(unique(vals.begin(), vals.end()) - vals.begin());

  for (int &i : a) {
    i = lower_bound(vals.begin(), vals.end(), i) - vals.begin();
  }

  vector<bool> split_vis(n - 1, true);
  vector<vector<int>> pos(n);
  vector<int> freq(n, 0);
  for (int i = 0; i < n - 1; i++) {
    if (a[i] == a[i + 1]) split_vis[i] = false;
    pos[a[i]].push_back(i);
    freq[a[i]]++;
  }

  TwoSat ts(n - 1);
  for (int i = 0; i < n; i++) {
    if (pos[i].size() >= 2) {
      ts.at_most_one(pos[i]);
    }
  }

  for (int l = 0; l < n; l++) {
    int r = l;
    while (r < n and a[r] == a[l]) r++;
    if (l > 0 and a[l - 1] == a[l] - 1 and
        r < n and a[r] == a[l] + 1 and
        r - l != freq[a[l]]
    ) {
      ts.either(~l, ~r);
    }
  }

  vector<int> splits;
  splits.push_back(-1);
  splits.push_back(n - 1);

  vector<vector<int>> pos(n);
  vector<int> first(n, -1), last(n, -1), freq(n, 0);

  for (int i = 0; i < n - 1; i++) {
    if (first[a[i]] == -1) first[a[i]] = i;
    last[a[i]] = i;
    freq[a[i]]++;
    if (a[i + 1] != a[i]) {
      if (a[i + 1] != a[i] + 1) splits.push_back(i);
      else pos[a[i]].push_back(i);
    }
  }

  vector<int> saved_at(n, -1);
  for (int i = 0; i < n; i++) {
    if (!pos[i].empty()) {
      if (i == 0 or
          saved_at[i - 1] == -1 or
          pos[i].size() > 1 or
          pos[i - 1].size() > 1 or
          first[i] - last[i] == freq[i]
      ) {
        saved_at[i]
      }
    }
  }

  sort(splits.begin(), splits.end());

  cout << (int)splits.size() - 1 << "\n";
  for (int i = 0; i < (int)splits.size() - 1; i++) {
    if (i) cout << " ";
    cout << splits[i + 1] - splits[i];
  }
  cout << "\n";

  return 0;
}