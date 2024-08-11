#include <bits/stdc++.h>
using namespace std;

vector<int> val, comp, z, cont;
int Time, ncomps;
template<class F>
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
template<class F>
void scc(vector<vector<int>> &g, F f) {
  int n = (int)g.size();
  val.assign(n, 0);
  comp.assign(n, -1);
  Time = ncomps = 0;
  for (int i = 0; i < n; i++) {
    if (comp[i] < 0) dfs(i, g, f);
  }
}

void test_case() {
  int n, m;
  cin >> n >> m;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<vector<int>> g(n);

  while (m--) {
    int from, to;
    cin >> from >> to;
    g[from - 1].push_back(to - 1);
  }

  vector<int> sz_dp(n, 0);
  vector<long long> a_dp(n, (long long)1e18);
  vector<int> comp_id(n, -1);

  int ans_sz = 0;
  long long ans_a = (long long)1e18;

  scc(
    g,
    [&](vector<int> &comp) {
      int cur_comp = comp[0];
      long long cur_a = 0ll;

      for (int i : comp) {
        comp_id[i] = cur_comp;
        cur_a += a[i];
      }

      sz_dp[cur_comp] = comp.size();
      a_dp[cur_comp] = cur_a;

      for (int from : comp) {
        for (int to : g[from]) {
          int to_comp = comp_id[to];
          if (to_comp != cur_comp) {
            int new_sz = comp.size() + sz_dp[to_comp];
            long long new_a = a_dp[to_comp] + cur_a;
            if (make_pair(new_sz, -new_a) > make_pair(sz_dp[cur_comp], -a_dp[cur_comp])) {
              sz_dp[cur_comp] = new_sz;
              a_dp[cur_comp] = new_a;
            }
          }
        }
      }

      if (make_pair(ans_sz, -ans_a) < make_pair(sz_dp[cur_comp], -a_dp[cur_comp])) {
        ans_sz = sz_dp[cur_comp];
        ans_a = a_dp[cur_comp];
      }
    }
  );

  cout << ans_sz << " " << ans_a << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}