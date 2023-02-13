#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int LOGN = 18;
const int TOT_C = 62;

int n;
vector<int> adj[N];
int disc[N];
int lv[N];
int par[N];
int P[LOGN][N];
int st[N], en[N];

void dfs(int at, int p, int &t) {
  st[at] = ++t;
  disc[at] = t;
  par[at] = p;
  if (at != 0) lv[at] = lv[p] + 1;
  for (int to : adj[at]) if (to != p) dfs(to, at, t);
  en[at] = t;
}

void initSp() {
  memset(P, -1, sizeof P);
  for (int i = 1; i <= n; i++) P[0][i] = par[i];
  for (int i = 1; i < LOGN; i++) {
    for (int j = 1; j <= n; j++) {
      if (P[i - 1][j] != -1) {
        P[i][j] = P[i - 1][P[i - 1][j]];
      }
    }
  }
}

int lca(int u, int v) {
  if (lv[u] < lv[v]) swap(u, v);
  for (int i = LOGN - 1; i >= 0; i--) {
    if (lv[u] - (1 << i) >= lv[v]) {
      u = P[i][u];
    }
  }
  if (u == v) return u;
  for (int i = LOGN - 1; i >= 0; i--) {
    if (P[i][u] != P[i][v]) u = P[i][u], v = P[i][v];
  }
  return par[u];
}

class BIT {
public:
  int n;
  vector<int> f;
  BIT(int n) : n(n) {
    f.resize(n + 1, 0);
  }
  void update(int p, int v) {
    while (p <= n) f[p] += v, p += p & -p;
  }
  void update(int l, int r, int v) {
    update(l, v);
    update(r + 1, -v);
  }
  int pref(int p) {
    int ret = 0;
    while (p) ret += f[p], p -= p & -p;
    return ret;
  }
};

int char_id(char c) {
  if ('a' <= c and c <= 'z') return c - 'a';
  if ('A' <= c and c <= 'Z') return 26 + (c - 'A');
  return 52 + (c - '0');
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;

  int q;
  cin >> q;

  string s;
  cin >> s;

  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  {
    int t = 0;
    dfs(1, -1, t);
    initSp();
  }

  vector<BIT> bit(TOT_C, BIT(n));
  for (int i = 0; i < n; i++) {
    int c = char_id(s[i]);
    bit[c].update(st[i + 1], en[i + 1], 1);
  }

  while (q--) {
    int type;
    cin >> type;

    if (type == 1) {
      int u, v;
      cin >> u >> v;
      int l = lca(u, v);
      int du = disc[u], dv = disc[v], dl = disc[l];

      int freq = -1;
      bool okay = true;
      for (int c = 0; c < TOT_C and okay; c++) {
        int curr_freq = 0;
        curr_freq += bit[c].pref(du);
        curr_freq += bit[c].pref(dv);
        curr_freq -= 2 * bit[c].pref(dl);
        curr_freq += char_id(s[l - 1]) == c;
        okay = curr_freq == 0 or freq == -1 or curr_freq == freq;
        if (curr_freq) freq = curr_freq;
      }

      cout << (okay ? "Yes" : "No") << "\n";
    }
    else {
      int v;
      char ch;
      cin >> v >> ch;
      int pc = char_id(s[v - 1]), nc = char_id(ch);
      s[v - 1] = ch;

      bit[pc].update(st[v], en[v], -1);
      bit[nc].update(st[v], en[v], 1);
    }
  }

  return 0;
}