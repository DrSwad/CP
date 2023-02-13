#include <bits/stdc++.h>
using namespace std;

const int P = 1e5;
const int S = 1e6;

vector<string> patterns;
vector<int> dp;

struct Trie {
  const int A = 26;
  int N;
  vector<vector<int>> next;
  vector<int> cnt;

  Trie() : N(0) {
    node();
  }

  int node() {
    next.emplace_back(A, -1);
    cnt.emplace_back(0);
    return N++;
  }

  inline int get(char c) {
    return c - 'a';
  }

  inline void insert(string &s) {
    int cur = 0;
    for (char c : s) {
      int to = get(c);
      if (next[cur][to] == -1)
        next[cur][to] = node();
      cur = next[cur][to];
    }
    cnt[cur]++;
  }

  vector<string> dfs() {
    stack<pair<int, int>> st;
    string s;
    vector<string> ret;

    for (st.push({0, -1}), s.push_back('$'); !st.empty(); ) {
      auto [u, c] = st.top();
      st.pop();
      s.pop_back();
      c++;
      if (c < A) {
        st.push({u, c});
        s.push_back(c + 'a');
        int v = next[u][c];
        if (~v) {
          if (cnt[v])
            ret.emplace_back(s);
          st.push({v, -1});
          s.push_back('$');
        }
      }
    }

    return ret;
  }
};

struct AC {
  int N, P;
  const int A = 26;
  vector<vector<int>> next;
  vector<int> link, out_link;
  vector<vector<int>> out;

  AC() : N(0), P(0) {
    node();
  }

  int node() {
    next.emplace_back(A, 0);
    link.emplace_back(0);
    out_link.emplace_back(0);
    out.emplace_back(0);
    return N++;
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
    out[u].push_back(P);
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
          out_link[v] =
            out[link[v]].empty() ? out_link[link[v]] : link[v];
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

  void match(const string &S) {
    int u = 0;
    int at = 0;
    for (auto c : S) {
      u = advance(u, c);
      at++;
      for (int v = u; v; v = out_link[v]) {
        for (auto p : out[v]) {
          int prev = dp[at - patterns[p].length()];
          if (prev != -1) {
            int curr = prev + 1;
            dp[at] = dp[at] == -1 ? curr : min(dp[at], curr);
          }
        }
      }
    }
  }
};

int main() {
  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    printf("Case %d: ", cs);

    int n;
    scanf("%d", &n);
    AC aho;
    Trie trie;

    char _p[P + 1];
    for (int i = 0; i < n; i++) {
      scanf("%s", _p);
      string p(_p);
      trie.insert(p);
    }
    patterns = trie.dfs();
    n = patterns.size();
    for (const string &p : patterns) {
      aho.add_pattern(p);
    }

    char _s[S];
    scanf("%s", _s);
    string s(_s);
    int len = s.length();
    dp.assign(len + 1, -1);
    dp[0] = 0;

    aho.compute();
    aho.match(s);

    if (dp[len] == -1)
      puts("impossible");
    else
      printf("%d\n", dp[len]);
  }

  return 0;
}