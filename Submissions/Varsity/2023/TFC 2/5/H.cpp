#include <bits/stdc++.h>
using namespace std;

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

  inline void insert(string s) {
    int cur = 0;
    for (char c : s) {
      int to = get(c);
      if (next[cur][to] == -1) next[cur][to] = node();
      cur = next[cur][to];
    }
    cnt[cur]++;
  }

  inline int find(string s) {
    int cur = 0;
    for (char c : s) {
      int to = get(c);
      if (next[cur][to] == -1) return 0;
      cur = next[cur][to];
    }
    return cnt[cur];
  }
};

struct Trie2D {
  const int A = 26;
  int N;
  vector<vector<int>> next;
  vector<Trie> cnt;

  Trie2D() : N(0) {
    node();
  }

  int node() {
    next.emplace_back(A, -1);
    cnt.emplace_back();
    return N++;
  }

  inline int get(char c) {
    return c - 'a';
  }

  inline void insert(string s1, string s2) {
    int cur = 0;
    for (char c : s1) {
      int to = get(c);
      if (next[cur][to] == -1) next[cur][to] = node();
      cur = next[cur][to];
    }
    cnt[cur].insert(s2);
  }

  inline int find(string s1, string s2) {
    int cur = 0;
    for (char c : s1) {
      int to = get(c);
      if (next[cur][to] == -1) return 0;
      cur = next[cur][to];
    }
    return cnt[cur].find(s2);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  string s;
  cin >> s;

  string s_l = s.substr(0, n);
  string s_r = s.substr(n, n);

  Trie2D trie;

  for (int mask = 0; mask < 1 << n; mask++) {
    string s1, s2;
    for (int i = 0; i < n; i++) {
      if (mask >> i & 1) s1 += s_l[i];
    }
    for (int i = n - 1; i >= 0; i--) {
      if (!(mask >> i & 1)) s2 += s_l[i];
    }
    trie.insert(s1, s2);
    // debug(s1, s2);
  }

  // debug(trie.N);

  long long ans = 0;
  for (int mask = 0; mask < 1 << n; mask++) {
    string s1, s2;
    for (int i = 0; i < n; i++) {
      if (mask >> i & 1) s1 += s_r[i];
    }
    for (int i = n - 1; i >= 0; i--) {
      if (!(mask >> i & 1)) s2 += s_r[i];
    }
    ans += trie.find(s2, s1);
    // debug(s2, s1);
  }

  cout << ans << "\n";

  return 0;
}