#include <bits/stdc++.h>
using namespace std;

const int LOGN = 20;

int n;
vector<vector<int>> e;
int q;
vector<pair<int, int>> vq;
vector<long long> vans;

vector<int> s;
void calculateS() {
  vector<set<int>> se;
  for (int i = 0; i < n; i++) {
    se.emplace_back(set<int>(e[i].begin(), e[i].end()));
  }

  s.assign(n, 0);
  vector<int> cur_que, nxt_que;
  for (int i = 0; i < n; i++) {
    if (se[i].size() <= 1) {
      cur_que.push_back(i);
      s[i] = 1;
    }
  }

  for (int val = 1; val <= n; val++) {
    for (int i = 0; i < cur_que.size(); i++) {
      int at = cur_que[i];
      assert(se[at].size() <= 2);
      for (auto it = se[at].begin(); it != se[at].end(); it++) {
        int nxt = *it;
        if (se[nxt].size() == 2 and !s[nxt]) {
          s[nxt] = val;
          cur_que.push_back(nxt);
        }
      }
    }

    for (auto it = cur_que.begin(); it != cur_que.end(); it++) {
      int at = *it;
      assert(se[at].size() <= 1);
      for (auto it = se[at].begin(); it != se[at].end(); it++) {
        int nxt = *it;
        se[nxt].erase(at);
        if (se[nxt].size() <= 1 and !s[nxt]) {
          nxt_que.push_back(nxt);
          s[nxt] = val + 1;
        }
      }
      se[at].clear();
    }

    swap(cur_que, nxt_que);
    nxt_que.clear();
  }

  assert(*min_element(s.begin(), s.end()) >= 1);
}

int root;
vector<int> h;
vector<int> up;
vector<vector<int>> jump;
void dfs(int at, int from) {
  h[at] = ~from ? h[from] + 1 : 0;
  up[at] = ~from ? s[from] == s[at] ? up[from] : from : -1;
  assert(up[at] == -1 or s[up[at]] > s[at]);
  jump[0][at] = from;
  for (auto it = e[at].begin(); it != e[at].end(); it++) {
    int to = *it;
    if (to != from) dfs(to, at);
  }
}

int lca(int u, int v) {
  if (h[u] < h[v]) {
    swap(u, v);
  }
  for (int i = LOGN - 1; i >= 0; i--) {
    if (h[u] - (1 << i) >= h[v]) {
      u = jump[i][u];
    }
  }
  if (u == v) {
    return u;
  }
  for (int i = LOGN - 1; i >= 0; i--) {
    if (jump[i][u] != jump[i][v]) {
      u = jump[i][u];
      v = jump[i][v];
    }
  }
  return jump[0][u];
}

long long query(int u, int v) {
  int w = lca(u, v);
  int pw = jump[0][w];
  int hw = h[w];
  int hpw = ~pw ? h[pw] : -1;
  vector<int> u_cnt(LOGN, 0), v_cnt(LOGN, 0);
  for (int at = u; ~at and h[at] > hpw; at = up[at]) {
    assert(s[at] < LOGN);
    u_cnt[s[at]] += h[at] - max(hpw, (~up[at] ? h[up[at]] : -1));
  }
  for (int at = v; ~at and h[at] > hw; at = up[at]) {
    assert(s[at] < LOGN);
    v_cnt[s[at]] += h[at] - max(hw, (~up[at] ? h[up[at]] : -1));
  }

  long long ans = 0;
  long long sum = 0;
  for (int i = 0; i < LOGN; i++) {
    ans += sum * 1ll * (u_cnt[i] + v_cnt[i]);
    sum += v_cnt[i];
  }

  return ans;
}

void solve() {
  calculateS();

  root = max_element(s.begin(), s.end()) - s.begin();
  assert(s[root] < LOGN);
  h.resize(n);
  up.resize(n);
  jump.assign(LOGN, vector<int>(n));
  dfs(root, -1);
  for (int i = 1; i < LOGN; i++) {
    for (int u = 0; u < n; u++) {
      jump[i][u] = ~jump[i - 1][u] ? jump[i - 1][jump[i - 1][u]] : -1;
    }
  }

  for (auto it = vq.begin(); it != vq.end(); it++) {
    int u = it->first;
    int v = it->second;
    vans.push_back(query(u, v));
  }
}

int main() {
  int t;
  cin >> t;

  while (t--) {
    scanf("%d %d", &n, &q);

    e.clear();
    e.resize(n);
    for (int i = 1; i < n; i++) {
      int u, v;
      scanf("%d %d", &u, &v);
      u--, v--;
      e[u].push_back(v);
      e[v].push_back(u);
    }

    vq.clear();
    for (int i = 0; i < q; i++) {
      int u, v;
      scanf("%d %d", &u, &v);
      u--, v--;
      vq.emplace_back(u, v);
    }

    vans.clear();

    solve();

    for (auto it = vans.begin(); it != vans.end(); it++) {
      printf("%lld\n", *it);
    }
  }

  return 0;
}