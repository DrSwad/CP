#include <bits/stdc++.h>
using namespace std;

struct AC {
  int N, P;
  const int A = 10;
  vector<vector<int>> next;
  vector<int> link;
  vector<int> out;
  vector<int> cnt;

  AC() : N(0), P(0) {
    node();
  }

  int node() {
    next.emplace_back(A, 0);
    link.emplace_back(0);
    out.emplace_back(0);
    cnt.emplace_back(0);
    return N++;
  }

  inline int get(char c) {
    return c - 'a';
  }

  int add_pattern(const string T, int type) {
    int u = 0;
    for (auto c : T) {
      if (!next[u][get(c)]) next[u][get(c)] = node();
      u = next[u][get(c)];
    }
    if (type == 0) {
      out[u] |= 1 << P;
      return P++;
    } else {
      cnt[u]++;
      return P;
    }
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
          out[v] |= out[link[v]];
          cnt[v] += cnt[link[v]];
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

  string solve() {
    vector<vector<int>> dp(1 << P, vector<int>(N, -1));
    vector<vector<int>> fromU(1 << P, vector<int>(N));
    vector<vector<char>> fromC(1 << P, vector<char>(N));
    vector<vector<int>> fromMask(1 << P, vector<int>(N));

    queue<pair<int, int>> q;
    q.push({0, 0});
    dp[0][0] = 0;
    int U = -1;

    while (!q.empty()) {
      auto [mask, u] = q.front();
      q.pop();
      if (mask == (1 << P) - 1) {
        U = u;
        break;
      }

      for (char c = 'a'; c < 'a' + A; c++) {
        int nu = next[u][get(c)];
        if (cnt[nu]) continue;
        int nmask = mask | out[nu];
        if (~dp[nmask][nu]) continue;

        dp[nmask][nu] = dp[mask][u] + 1;
        fromU[nmask][nu] = u;
        fromC[nmask][nu] = c;
        fromMask[nmask][nu] = mask;
        q.push({nmask, nu});
      }
    }

    string ans;
    if (~U) {
      int u = U;
      int mask = (1 << P) - 1;
      while (u or mask) {
        int nu = fromU[mask][u];
        int nc = fromC[mask][u];
        int nmask = fromMask[mask][u];
        if (nc) ans += nc;
        u = nu;
        mask = nmask;
      }
      reverse(ans.begin(), ans.end());
    }
    else ans = "-";

    return ans;
  }
};
// Don't forget to call compute()!

int main() {
  int n, m;
  scanf("%d %d", &n, &m);

  AC aho;
  while (n--) {
    string s;
    cin >> s;
    aho.add_pattern(s, 0);
  }
  while (m--) {
    string s;
    cin >> s;
    aho.add_pattern(s, 1);
  }

  aho.compute();
  cout << aho.solve() << endl;

  return 0;
}