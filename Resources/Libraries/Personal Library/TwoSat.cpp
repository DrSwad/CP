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