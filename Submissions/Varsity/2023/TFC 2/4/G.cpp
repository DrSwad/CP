#include <bits/stdc++.h>
using namespace std;

struct Trie {
  const int A = 26;
  int N;
  vector<vector<int>> next;

  Trie() : N(0) {
    node();
  }

  int node() {
    next.emplace_back(A, -1);
    return N++;
  }

  inline int get(char c) {
    return c - 'a';
  }

  inline void insert(string s) {
    int cur = 0;
    for (char c : s) {
      int to = get(c);
      if (next[cur][to] == -1) next[cur][to] = node();
      cur = next[cur][to];
    }
  }

  vector<int> dfs_order;
  vector<bool> is_leaf;
  void dfs(int at = 0) {
    int children = 0;
    for (int c = 0; c < A; c++) {
      if (next[at][c] != -1) {
        children++;
        dfs(next[at][c]);
      }
    }
    dfs_order.push_back(at);
    if (children == 0) is_leaf[at] = true;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  Trie trie;

  while (n--) {
    string s;
    cin >> s;
    trie.insert(s);
  }

  n = trie.N;
  trie.is_leaf.resize(n, false);
  trie.dfs();
  vector<bool> is_leaf = trie.is_leaf;
  vector<int> dfs_order = trie.dfs_order;

  vector<bool> dp(2);
  for (int st = 0; st < 2; st++) {
    vector<bool> state(n, false);
    for (int i = 0; i < n; i++) {
      int at = dfs_order[i];
      if (is_leaf[at]) state[at] = st;
      else {
        for (int c = 0; c < trie.A; c++) {
          int to = trie.next[at][c];
          if (to != -1) {
            if (!state[to]) {
              state[at] = true;
              break;
            }
          }
        }
      }
    }
    dp[st] = state[0];
  }

  if (dp[0] == 0) cout << "Second\n";
  else if (k == 1) cout << "First\n";
  else if (dp[1] == 1) cout << "First\n";
  else if (k % 2 == 1) cout << "First\n";
  else cout << "Second\n";

  return 0;
}