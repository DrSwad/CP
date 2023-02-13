#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e6 + 5;

int n, k;
int div_count[N];
int par[N];
vector<int> e[N];
vector<vector<int>> cycles;
bool in_cycle[N];

void sieve() {
  for (int i = 1; i < n; i++) {
    for (int j = i; j < n; j += i) {
      div_count[j]++;
    }
  }
}

vector<int> st;
int vis[N];

void cycle_dfs(int at) {
  vis[at] = 1;
  st.push_back(at);
  debug() << name(at);

  if (~par[at]) {
    if (vis[par[at]] == 0) cycle_dfs(par[at]);
    else if (vis[par[at]] == 1) {
      vector<int> new_cycle;
      for (int i = st.size() - 1; st[i] != par[at]; i--) {
        new_cycle.push_back(st[i]);
        assert(i > 0);
      }
      new_cycle.push_back(par[at]);
      reverse(new_cycle.begin(), new_cycle.end());
      cycles.emplace_back(new_cycle);
    }
  }

  st.pop_back();
  vis[at] = 2;
}

vector<tuple<ll, int, int>> dfs_data;
ll curr_sum;

void dfs(int at, int path = 0) {
  if (st.size() >= k) curr_sum -= st[st.size() - k];
  st.push_back(at);
  curr_sum += at;

  dfs_data.emplace_back(curr_sum, path, at);

  for (int to : e[at]) {
    if (!in_cycle[to]) {
      dfs(to, path + 1);
    }
  }

  st.pop_back();
  curr_sum -= at;
  if (st.size() >= k) curr_sum += st[st.size() - k];
}

int main() {
  scanf("%d %d", &n, &k);
  if (k > n) {
    puts("-1");
    return 0;
  }

  sieve();

  par[0] = -1;
  for (int i = 1; i < n; i++) {
    par[i] = (i + div_count[i]) % n;
    e[par[i]].push_back(i);
  }

  for (int i = 0; i < n; i++) {
    if (!vis[i]) cycle_dfs(i);
  }

  cycles.push_back(vector<int>(1, 0));
  // debug() << name(cycles);

  ll ans = -1;
  int ans_from;

  for (vector<int> &cycle : cycles) {
    int len = cycle.size();
    vector<ll> pref(len);
    for (int i = 0; i < len; i++) {
      in_cycle[cycle[i]] = true;
      pref[i] = (ll)cycle[i] + (i ? pref[i - 1] : 0);
    }
    // debug() << name(cycle);

    auto range_sum = [&](int st, int sz) {
      assert(sz <= len);
      int en = st + (sz - 1);
      if (en >= len) en -= len;
      ll ret = pref[en] - (st ? pref[st - 1] : 0);
      if (ret < 0) ret += pref[len - 1];
      return ret;
    };

    for (int i = 0; i < len; i++) {
      dfs_data.clear();
      curr_sum = 0;
      st.clear();
      dfs(cycle[i]);
      // debug() << name(i);

      for (auto [sum, path, to] : dfs_data) {
        // debug() << name(sum) name(path) name(to);
        if (path < k) {
          if (k - path > len) continue;
          sum -= cycle[i];
          sum += range_sum(i, k - path);
        }
        // debug() << name(sum);
        if (ans == -1 or sum < ans) {
          ans = sum;
          ans_from = to;
        }
      }
    }
  }

  // debug() << name(ans_from);

  for (int i = 0, at = ans_from; i < k; i++, at = par[at]) {
    if (i) printf(" ");
    printf("%d", at);
  }
  puts("");

  return 0;
}