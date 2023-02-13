/**
 * Time: O(E + V)
 * Usage: scc(graph, [\&](vector<int>\& v) { ... }) visits all
 * components in reverse topological order. comp[i] holds the
 * component index of a node (a component only has edges to components
 * with lower index). ncomps will contain the number of components.
 * Everything 0-indexed.
 */

vector<int> val, comp, z, cont;
int Time, ncomps;
template <class F>
int dfs(int j, vector<vector<int>> &g, F &f) {
  int low = val[j] = ++Time, x;
  z.push_back(j);
  for (auto e : g[j]) {
    if (comp[e] < 0) {
      low = min(low, val[e] ?: dfs(e, g, f));
    }
  }

  if (low == val[j]) {
    do {
      x = z.back();
      z.pop_back();
      comp[x] = ncomps;
      cont.push_back(x);
    } while (x != j);
    f(cont);
    cont.clear();
    ncomps++;
  }
  return val[j] = low;
}
template <class F>
void scc(vector<vector<int>> &g, F f) {
  int n = (int)g.size();
  val.assign(n, 0);
  comp.assign(n, -1);
  Time = ncomps = 0;
  for (int i = 0; i < n; i++) {
    if (comp[i] < 0) dfs(i, g, f);
  }
}