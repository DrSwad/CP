#include <bits/stdc++.h>
using namespace std;

struct Trie {
  int A = 26;
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

  inline void insert(string s) {
    int cur = 0;
    for (char c : s) {
      int to = get(c);
      if (next[cur][to] == -1) next[cur][to] = node();
      cur = next[cur][to];
    }
    cnt[cur]++;
  }

  inline bool find(string s) {
    int cur = 0;
    for (char c : s) {
      int to = get(c);
      if (next[cur][to] == -1) return false;
      cur = next[cur][to];
    }
    return (cnt[cur] != 0);
  }

  // Doesn't check for existence
  inline void erase(string s) {
    int cur = 0;
    for (char c : s) {
      int to = get(c);
      cur = next[cur][to];
    }
    cnt[cur]--;
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
          if (cnt[v]) ret.emplace_back(s);
          st.push({v, -1});
          s.push_back('$');
        }
      }
    }

    return ret;
  }
};

int main() {
  return 0;
}