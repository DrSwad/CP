#include <bits/stdc++.h>
using namespace std;

struct AC {
  int N, P;
  int A = 26;
  vector<vector<int>> next;
  vector<int> link;
  vector<int> out;
  vector<string> pat;

  AC() : N(0), P(0) {
    node();
  }

  int node() {
    next.emplace_back(A, 0);
    link.emplace_back(0);
    out.emplace_back(0);
    return N++;
  }

  void clear() {
    next.clear();
    link.clear();
    out.clear();
    pat.clear();
    N = P = 0;
    node();
  }

  inline int get(char c) {
    return c - 'a';
  }

  int add_pattern(const string T) {
    int u = 0;
    for (auto c : T) {
      if (!next[u][get(c)]) next[u][get(c)] = node();
      u = next[u][get(c)];
    }
    out[u] = 1;
    pat.emplace_back(T);
    return P++;
  }

  void compute() {
    queue<int> q;
    for (q.push(0); !q.empty(); ) {
      int u = q.front();
      q.pop();
      for (int c = 0; c < A; ++c) {
        int v = next[u][c];
        if (!v) {next[u][c] = next[link[u]][c];}
        else {
          link[v] = u ? next[link[u]][c] : 0;
          out[v] += out[link[v]];
          q.push(v);
        }
      }
    }
  }

  int advance(int u, char c) {
    while (u && !next[u][get(c)]) u = link[u];
    u = next[u][get(c)];
    return u;
  }

  long long match(const string S) {
    int u = 0;
    long long ret = 0;
    for (auto c : S) {
      u = advance(u, c);
      ret += out[u];
    }
    return ret;
  }
};

const int LOG = 23;
struct DAC {
  AC aho[LOG];

  void add_pattern(const string &s) {
    int pos;
    for (pos = 0; pos < LOG; pos++) {
      if (aho[pos].P == 0) break;
    }

    aho[pos].add_pattern(s);

    for (int i = 0; i < pos; i++) {
      for (const string &curr : aho[i].pat) {
        aho[pos].add_pattern(curr);
      }
      aho[i].clear();
    }

    aho[pos].compute();
  }

  long long match(const string &s) {
    long long ret = 0;
    for (int i = 0; i < LOG; i++) {
      ret += aho[i].match(s);
    }
    return ret;
  }
};

const int N = 3e5 + 5;

int main() {
  int n;
  scanf("%d", &n);

  DAC add_aho, del_aho;
  char _s[N];
  for (int i = 1; i <= n; i++) {
    int type;
    scanf("%d", &type);
    scanf("%s", _s);
    string s(_s);

    if (type == 1) {
      add_aho.add_pattern(s);
    } else if (type == 2) {
      del_aho.add_pattern(s);
    } else {
      long long ans = 0;
      ans += add_aho.match(s);
      ans -= del_aho.match(s);
      cout << ans << endl;
    }
  }

  return 0;
}