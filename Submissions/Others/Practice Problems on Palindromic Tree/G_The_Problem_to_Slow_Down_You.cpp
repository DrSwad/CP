#include <bits/stdc++.h>
using namespace std;

const int A = 26;
const int N = 2e5 + 5;

struct Ptree {
  string s;
  int last, ptr;
  vector<vector<int>> nxt;
  vector<int> link, len, occ, depth, end_at;
  Ptree(string s) {
    this->s = " " + s;
    int sz = s.length() + 5;
    nxt.resize(sz, vector<int>(A, 0));
    link.resize(sz, 0);
    len.resize(sz, 0);
    occ.resize(sz, 0);
    depth.resize(sz, 0);
    end_at.resize(sz, 0);
    len[1] = -1, len[2] = 0, link[1] = link[2] = 1, last = ptr = 2;
  }
  void feed(int at) {
    while (s[at - len[last] - 1] != s[at]) last = link[last];
    int ch = s[at] - 'a', temp = link[last];
    while (s[at - len[temp] - 1] != s[at]) temp = link[temp];
    if (!nxt[last][ch]) {
      nxt[last][ch] = ++ptr, len[ptr] = len[last] + 2;
      link[ptr] = len[ptr] == 1 ? 2 : nxt[temp][ch];
      depth[ptr] = depth[link[ptr]] + 1;
    }
    last = nxt[last][ch], ++occ[last];
    end_at[at] = depth[last];
  }
};

int main() {
  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    printf("Case #%d: ", cs);

    vector<Ptree> pt;
    for (int it = 0; it < 2; it++) {
      string s;
      cin >> s;
      Ptree _pt(s);
      for (int i = 0; i < s.length(); i++) {
        _pt.feed(i + 1);
      }
      for (int i = _pt.ptr; i > 2; i--) {
        _pt.occ[_pt.link[i]] += _pt.occ[i];
      }
      pt.emplace_back(_pt);
    }

    long long ans = 0;
    function<void(int, int)> dfs = [&](int at0, int at1) {
      for (int c = 0; c < A; c++) {
        int nxt0 = pt[0].nxt[at0][c];
        int nxt1 = pt[1].nxt[at1][c];
        if (nxt0 and nxt1) {
          ans += 1ll * pt[0].occ[nxt0] * pt[1].occ[nxt1];
          dfs(nxt0, nxt1);
        }
      }
    };
    dfs(1, 1);
    dfs(2, 2);
    printf("%lld\n", ans);
  }

  return 0;
}