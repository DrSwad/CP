#include <bits/stdc++.h>
using namespace std;

int n, L;
string s;

vector<int> iden() {
  int nn = n * n;
  vector<int> p(nn);
  iota(p.begin(), p.end(), 0);
  return p;
}

vector<int> mul(const vector<int> &p1, const vector<int> &p2) {
  int nn = n * n;
  vector<int> p(nn);
  for (int i = 0; i < nn; i++) {
    p[i] = p2[p1[i]];
  }
  return p;
}

vector<int> repeat(const vector<int> &p, int num) {
  vector<vector<int>> cycles;
  int nn = n * n;
  vector<bool> vis(nn, false);
  for (int i = 0; i < nn; i++) {
    if (!vis[i]) {
      vector<int> cycle;
      int at = i;
      while (!vis[at]) {
        cycle.push_back(at);
        vis[at] = true;
        at = p[at];
      }
      cycles.push_back(cycle);
    }
  }

  vector<int> ret(nn);
  for (const auto &cycle : cycles) {
    int len = cycle.size();
    int jump = num % len;
    vector<bool> vis(len, false);
    for (int i = 0; i < len; i++) {
      if (!vis[i]) {
        vector<int> ncycle;
        int at = i;
        while (!vis[at]) {
          ncycle.push_back(cycle[at]);
          vis[at] = true;
          at = at + jump;
          if (at >= len) at -= len;
        }
        for (int ni = 0, nlen = ncycle.size(); ni < nlen; ni++) {
          int nj = ni + 1;
          if (nj == nlen) nj = 0;
          ret[ncycle[ni]] = ncycle[nj];
        }
      }
    }
  }

  return ret;
}

vector<int> op(char c, int num) {
  num--;
  assert(0 <= num and num < n);
  vector<int> p = iden();
  if (c == 'L') {
    int row = num, st = row * n, en = (row + 1) * n;
    for (int at = st; at < en; at++) {
      p[at] = at - 1;
    }
    p[st] = en - 1;
  }
  else if (c == 'R') {
    int row = num, st = row * n, en = (row + 1) * n;
    for (int at = st; at < en; at++) {
      p[at] = at + 1;
    }
    p[en - 1] = st;
  }
  else if (c == 'U') {
    int col = num, st = col, en = n * n + col;
    for (int at = st; at < en; at += n) {
      p[at] = at - n;
    }
    p[st] = en - n;
  }
  else {
    assert(c == 'D');
    int col = num, st = col, en = n * n + col;
    for (int at = st; at < en; at += n) {
      p[at] = at + n;
    }
    p[en - n] = st;
  }

  return p;
}

vector<int> parse(int &at) {
  vector<int> ret = iden();
  if (at >= L) return ret;

  int st = at;
  int en = st;
  for (st = en; st < L; st = en) {
    if (s[en] == 'L' or s[en] == 'R' or s[en] == 'U' or s[en] == 'D') {
      int num = 0;
      en++;
      while (en < L and '0' <= s[en] and s[en] <= '9') {
        num = num * 10 + (s[en] - '0');
        en++;
      }
      assert(num > 0);
      ret = mul(ret, op(s[st], num));
    }
    else if (s[en] == '(') {
      en++;
      vector<int> nested = iden();
      while (s[en] != ')') {
        nested = mul(nested, parse(en));
      }
      assert(en < L and s[en] == ')');
      int num = 0;
      en++;
      while (en < L and '0' <= s[en] and s[en] <= '9') {
        num = num * 10 + (s[en] - '0');
        en++;
      }
      assert(num > 0);
      ret = mul(ret, repeat(nested, num));
    }
    else {
      break;
    }
  }

  at = en;
  return ret;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> L;
  cin >> s;
  L = s.length();

  vector<int> p = iden();
  for (int i = 0; i < L; ) {
    p = mul(p, parse(i));
  }

  int nn = n * n;
  vector<int> ans(nn);
  for (int i = 0; i < nn; i++) {
    ans[p[i]] = i;
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (j) cout << " ";
      cout << ans[i * n + j] + 1;
    }
    cout << "\n";
  }

  return 0;
}