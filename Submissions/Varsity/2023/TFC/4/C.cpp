#include <bits/stdc++.h>
using namespace std;

const int L = 8;

struct Trie {
  const int A = 26 * 2 + 10;
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
    if ('a' <= c and c <= 'z') return c - 'a';
    if ('A' <= c and c <= 'Z') return 26 + c - 'A';
    if ('0' <= c and c <= '9') return 52 + c - 'A';
    assert(false);
  }

  inline void insert(string s) {
    int cur = 0;
    cnt[cur]++;
    for (char c : s) {
      int to = get(c);
      if (next[cur][to] == -1) next[cur][to] = node();
      cur = next[cur][to];
      cnt[cur]++;
    }
  }

  inline int query(string s) {
    int cur = 0;
    for (char c : s) {
      int to = get(c);
      if (next[cur][to] == -1) return 0;
      cur = next[cur][to];
    }
    return cnt[cur];
  }
};

Trie freq1[L];
Trie freq2[L][L];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int q, n;
  cin >> q >> n;

  vector<string> ns(n);
  for (string &s : ns) cin >> s;
  sort(ns.begin(), ns.end());

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < L; j++) {
      string s = ns[i];
      s.erase(s.begin() + j);
      freq1[j].insert(s);
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < L; j++) {
      for (int k = j + 1; k < L; k++) {
        string s = ns[i];
        s.erase(s.begin() + k);
        s.erase(s.begin() + j);
        freq2[j][k].insert(s);
      }
    }
  }

  while (q--) {
    string qs;
    int d;
    cin >> qs >> d;

    int cnt0 = 0;
    {
      auto [itL, itU] = equal_range(ns.begin(), ns.end(), qs);
      cnt0 = itU - itL;
    }

    if (d == 0) {
      cout << cnt0 << "\n";
      continue;
    }

    int cnt1 = 0;
    {
      for (int j = 0; j < L; j++) {
        string s = qs;
        s.erase(s.begin() + j);
        cnt1 += freq1[j].query(s);
      }
      cnt1 -= 8 * cnt0;
    }

    if (d == 1) {
      cout << cnt1 << "\n";
      continue;
    }

    int cnt2 = 0;
    {
      for (int j = 0; j < L; j++) {
        for (int k = j + 1; k < L; k++) {
          string s = qs;
          s.erase(s.begin() + k);
          s.erase(s.begin() + j);
          cnt2 += freq2[j][k].query(s);
        }
      }

      cnt2 -= (8 * 7 / 2) * cnt0;
      cnt2 -= 7 * cnt1;
    }

    cout << cnt2 << "\n";
  }

  return 0;
}