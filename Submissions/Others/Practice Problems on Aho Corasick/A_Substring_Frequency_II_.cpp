#include <bits/stdc++.h>
using namespace std;

struct AC {
  int N, P;
  const int A = 26;
  vector<vector<int>> next;
  vector<int> link, out_link;
  vector<unordered_map<int, int>> out;

  AC() : N(0), P(0) {
    node();
  }

  int node() {
    next.emplace_back(A, 0);
    link.emplace_back(0);
    out_link.emplace_back(0);
    out.emplace_back();
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
    out[u][P]++;
    return P++;
  }

  void compute() {
    queue<int> q;
    for (q.push(0); !q.empty(); ) {
      int u = q.front();
      q.pop();
      for (int c = 0; c < A; ++c) {
        int v = next[u][c];
        if (!v) { next[u][c] = next[link[u]][c];}
        else {
          link[v] = u ? next[link[u]][c] : 0;
          for (auto [p, freq] : out[link[v]]) {
            out[v][p] += freq;
          }
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

  vector<int> match(const string S) {
    vector<int> matches(P, 0);
    int u = 0;
    for (auto c : S) {
      u = advance(u, c);
      for (auto [p, freq] : out[u]) {
        matches[p] += freq;
      }
    }
    return matches;
  }
};

int main() {
  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    printf("Case %d:\n", cs);

    int n;
    scanf("%d", &n);

    char _s[1000001];
    scanf("%s", _s);
    string s(_s);

    AC aho;
    for (int i = 0; i < n; i++) {
      char _p[501];
      scanf("%s", _p);
      string p(_p);
      aho.add_pattern(p);
    }

    aho.compute();

    vector<int> matches = aho.match(s);
    for (int freq : matches) {
      printf("%d\n", freq);
    }
  }

  return 0;
}