#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e5 + 5;
int nn; bool isCentroid[MAX]; int sub[MAX]; // internal, won't need anymore
vector<int> ed[MAX]; // original graph adjacency list
int cpar[MAX]; // parent node in CD graph
int clevel[MAX]; // level in CD graph
int dis[20][MAX]; // distance of node from the centroid at i'th level
void calcSubTree(int s, int p) {
  sub[s] = 1;
  for (int x : ed[s]) {
    if (x == p or isCentroid[x]) continue;
    calcSubTree(x, s);
    sub[s] += sub[x];
  }
}
int getCentroid(int s, int p) {
  for (int x : ed[s]) {
    if (!isCentroid[x] && x != p && sub[x] > (nn / 2)) return getCentroid(x, s);
  }
  return s;
}
void setDis(int s, int from, int p, int lev) {
  dis[from][s] = lev;
  for (int x : ed[s]) {
    if (x == p or isCentroid[x]) continue;
    setDis(x, from, s, lev + 1);
  }
}
void decompose(int s, int p, int lev) {
  calcSubTree(s, p); nn = sub[s];
  int c = getCentroid(s, p);
  setDis(c, lev, p, 0);
  isCentroid[c] = true; cpar[c] = p; clevel[c] = lev;
  for (int x : ed[c]) {
    if (!isCentroid[x]) decompose(x, c, lev + 1);
  }
}

typedef long long ll;
int n;
set<pair<ll, int>> cd_reqs[MAX];
int qc[MAX];
ll qt[MAX];

void reset() {
  for (int i = 0; i < MAX; i++) {
    ed[i].clear();
    cd_reqs[i].clear();
  }

  memset(isCentroid, false, sizeof isCentroid);
  memset(sub, 0, sizeof sub);
  memset(cpar, 0, sizeof cpar);
  memset(clevel, 0, sizeof clevel);
  memset(dis, 0, sizeof dis);
}

void test_case() {
  reset();

  cin >> n;
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    ed[u].push_back(v);
    ed[v].push_back(u);
  }

  nn = n; decompose(1, -1, 0);

  int q;
  cin >> q;
  for (int qi = 0; qi < q; qi++) {
    ll t;
    int c;
    cin >> t >> c;
    qt[qi] = t;
    qc[qi] = c;
  }

  int qi = 0;
  int at_c = 1;
  ll at_time = 0;
  vector<ll> ans;

  for (int done = 0; done < q; done++) {
    while (qi < q and qt[qi] <= at_time or qi <= done) {
      int c = qc[qi];
      int p = qc[qi];
      while (p != -1) {
        int level = clevel[p];
        ll d = dis[level][c];
        cd_reqs[p].insert({d, qi});
        p = cpar[p];
      }
      at_time = max(at_time, qt[qi]);

      qi++;
    }

    int nxt_qi = n + 1;
    ll nxt_dist = LLONG_MAX;
    int c = at_c;
    int p = at_c;
    while (p != -1) {
      if (!cd_reqs[p].empty()) {
        int level = clevel[p];
        auto [d, _qi] = *cd_reqs[p].begin();
        d = d + dis[level][c];
        if (make_pair(d, _qi) < make_pair(nxt_dist, nxt_qi)) {
          nxt_qi = _qi;
          nxt_dist = d;
        }
      }
      p = cpar[p];
    }

    {
      int c = qc[nxt_qi];
      int p = qc[nxt_qi];
      while (p != -1) {
        int level = clevel[p];
        ll d = dis[level][c];
        cd_reqs[p].erase({d, nxt_qi});
        p = cpar[p];
      }
    }

    at_c = qc[nxt_qi];
    at_time += nxt_dist;
    ans.push_back(at_c);
  }

  for (ll i : ans) {
    cout << " " << i;
  }
  cout << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case " << cs << ":";
    test_case();
  }

  return 0;
}