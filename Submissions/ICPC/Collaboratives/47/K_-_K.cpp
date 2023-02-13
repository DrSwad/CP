#include <bits/stdc++.h>
using namespace std;

struct Trie {
  const int A = 26;
  int N;
  vector<vector<int>> next;
  vector<int> set_id;

  Trie() : N(0) {
    node();
  }

  int node() {
    next.emplace_back(A, -1);
    set_id.emplace_back(-1);
    return N++;
  }

  inline int get(char c) {
    return c - 'a';
  }

  inline void insert(string s, int sid) {
    int cur = 0;
    for (char c : s) {
      int to = get(c);
      if (next[cur][to] == -1) next[cur][to] = node();
      cur = next[cur][to];
    }
    set_id[cur] = sid;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  vector<pair<string, string>> v;
  {
    string s;
    while (cin >> s) {
      string os = s;
      sort(os.begin(), os.end());
      v.push_back({s, os});
    }
  }

  int n = v.size();
  sort(v.begin(), v.end());

  Trie trie;
  map<string, int> mp;
  vector<vector<int>> equals(n);
  for (int i = 0; i < n; i++) {
    if (mp.find(v[i].second) == mp.end()) {
      mp[v[i].second] = i;
      trie.insert(v[i].second, i);
    }
    equals[mp[v[i].second]].push_back(i);
  }

  vector<bool> set_vis(n, false);

  for (int i = 0; i < n; i++) {
    string s = v[i].second;
    int len = s.length();
    int full = (1 << len) - 1;
    stack<int> masks;
    for (int mask = full & (full - 1); mask > 0; mask = full & (mask - 1)) {
      masks.push(mask);
    }

    vector<int> trie_node(1 << len);
    trie_node[0] = 0;

    while (!masks.empty()) {
      int mask = masks.top();
      masks.pop();
      int msb = 31 - __builtin_clz(mask);
      int prv_mask = mask - (1 << msb);
      trie_node[mask] = trie_node[prv_mask] == -1 ? -1 : trie.next[trie_node[prv_mask]][s[msb] - 'a'];
      if (trie_node[mask] != -1) {
        int sid = trie.set_id[trie_node[mask]];
        if (sid != -1) set_vis[sid] = true;
      }
    }
  }

  vector<bool> vis(n, false);
  for (int i = 0; i < n; i++) {
    if (set_vis[i]) {
      for (int j : equals[i]) vis[j] = true;
    }
  }

  for (int i = 0; i < n; i++) {
    if (!vis[i]) {
      cout << v[i].first << "\n";
    }
  }

  return 0;
}