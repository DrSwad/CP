#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz = 1e6 + 5;

char s[sz];
ll dp[sz][55];

struct Corasick {
  bool out[sz];
  int nd, pt, next[sz][2], link[sz], out_link[sz];
  vector<int>bfs;

  void renew() {
    nd = pt = 0;
    bfs.clear();
    node();
  }

  int node() {
    memset(next[nd], 0, sizeof next[nd]);
    link[nd] = out_link[nd] = 0;
    return nd++;
  }

  inline int fnc(char c) {
    return c - '0';
  }

  void add_pat(string s) {
    int u = 0;
    for (char c : s) {
      int &v = next[u][fnc(c)];
      if (!v) v = node();
      u = v;
    }
    out[u] = 1;
    pt++;
  }

  void automate() {
    bfs.push_back(0);
    for (int i = 0; i < bfs.size(); i++) {
      int u = bfs[i];
      for (int x = 0; x < 2; x++) {
        int &v = next[u][x], w = next[link[u]][x];
        if (!v) {
          v = w;
        } else {
          int r = link[v] = u ? w : 0;
          out_link[v] = !out[r] ? out_link[r] : r;
          bfs.push_back(v);
        }
      }
    }
    reverse( bfs.begin(), bfs.end() );
    bfs.pop_back();
  }

  ll fnc(int u, int r) {
    if (r < 0)
      return 0;
    ll &w = dp[u][r];
    if (w >= 0)
      return w;
    if (out[u])
      return w = 1LL << r;
    return w = fnc(next[u][0], r - 1) + fnc(next[u][1], r - 1);
  }
} aho;

int main() {
  int n;
  scanf("%d %s", &n, s);
  aho.renew();
  vector<int>p;
  for (int i = 0; s[i]; i++) {
    if (s[i] == '*') p.push_back(i);
  }
  string s = "\t";
  int m = p.size();
  for (int i = 0; i < 1 << m; i++) {
    for (int j = 0; j < m; j++) {
      if (i & 1 << j) s[p[j]] = '1';
      else s[p[j]] = '0';
    }
    aho.add_pat(s);
  }
  aho.automate();
  memset( dp, -1, sizeof(dp) );
  printf( "%lld\n", aho.fnc(0, n) );

  return 0;
}