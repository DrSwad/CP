#include <bits/stdc++.h>
using namespace std;

struct Trie {
  const int H = 30;
  int n;
  vector<vector<int>> next;
  vector<int> cnt, dp, val;

  Trie() : n(0) {
    node();
  }

  int node() {
    next.emplace_back(2, -1);
    cnt.emplace_back(0);
    dp.emplace_back(-1);
    val.emplace_back(-1);
    return n++;
  }

  void merge(int at, int bit) {
    int &left = next[at][0];
    if (left == -1) left = node();

    int &right = next[at][1];
    if (right == -1) right = node();

    cnt[at] = cnt[left] + cnt[right];

    if (cnt[at] != 1) val[at] = -1;
    else val[at] = val[left] != -1 ? val[left] : val[right] + (1 << bit);

    if (dp[left] != -1) {
      if (dp[right] != -1) {
        dp[at] = min(dp[left], dp[right]);
      }
      else {
        dp[at] = dp[left];
      }
    }
    else {
      if (dp[right] != -1) {
        dp[at] = dp[right];
      }
      else if (val[left] != -1 and val[right] != -1) {
        dp[at] = (val[left] ^ val[right]) | 1 << bit;
      }
      else dp[at] = -1;
    }
  }

  void insert(int x) {
    int at = 0;
    stack<int> st;
    for (int i = H - 1; i >= 0; i--) {
      st.push(at);
      int to = x >> i & 1;
      if (next[at][to] == -1) next[at][to] = node();
      at = next[at][to];
    }

    cnt[at]++;
    dp[at] = cnt[at] >= 2 ? 0 : -1;
    val[at] = cnt[at] == 1 ? 0 : -1;
    int bit = -1;

    while (!st.empty()) {
      int at = st.top();
      st.pop();
      merge(at, ++bit);
    }
  }

  void erase(int x) {
    int at = 0;
    stack<int> st;
    for (int i = H - 1; i >= 0; i--) {
      st.push(at);
      int to = x >> i & 1;
      assert(next[at][to] != -1);
      at = next[at][to];
    }

    cnt[at]--;
    dp[at] = cnt[at] >= 2 ? 0 : -1;
    val[at] = cnt[at] == 1 ? 0 : -1;
    int bit = -1;

    while (!st.empty()) {
      int at = st.top();
      st.pop();
      merge(at, ++bit);
    }
  }

  int query() {
    return dp[0];
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int q;
  cin >> q;

  Trie trie;

  while (q--) {
    int type;
    cin >> type;

    if (type == 1) {
      int x;
      cin >> x;
      trie.insert(x);
    }
    else if (type == 2) {
      int x;
      cin >> x;
      trie.erase(x);
    }
    else {
      cout << trie.query() << "\n";
    }
  }

  return 0;
}