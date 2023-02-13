#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
array<vi, 2> manacher(const string&s) {
  int n = s.length();
  array<vi, 2> p = {vi(n + 1), vi(n)};
  for (int z = 0; z < 2; z++) for (int i = 0, l = 0, r = 0; i < n; i++) {
      int t = r - i + !z;
      if (i < r) p[z][i] = min(t, p[z][l + t]);
      int L = i - p[z][i], R = i + p[z][i] - !z;
      while (L >= 1 && R + 1 < n && s[L - 1] == s[R + 1]) p[z][i]++, L--, R++;
      if (R > r) l = L, r = R;
    }
  return p;
}

int count_palindrome_substrings(string s) {
  /* int n = s.length();
     int ret = 0;

     for (int i = 0; i < n; i++) {
     ret++;
     for (int l = i - 1, r = i + 1; l >= 0 and r < n and s[l] == s[r]; l--, r++) {
      ret++;
     }
     for (int l = i, r = i + 1; l >= 0 and r < n and s[l] == s[r]; l--, r++) {
      ret++;
     }
     }

     return ret; */

  auto res = manacher(s);
  int ret = 0;
  for (auto i : res) {
    for (auto j : i) {
      ret += j;
    }
  }
  return ret + s.length();
}

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

  inline void insert(string s, int index) {
    int cur = 0;
    for (char c : s) {
      int to = get(c);
      if (next[cur][to] == -1) next[cur][to] = node();
      cur = next[cur][to];
    }
    cnt[cur] = index;
  }

  inline int find(string s) {
    int cur = 0;
    for (char c : s) {
      int to = get(c);
      if (next[cur][to] == -1) return false;
      cur = next[cur][to];
    }
    return cnt[cur];
  }
};

int palindromes_at[1000];

void test_case() {
  int n, q;
  cin >> n >> q;

  vector<pair<int, int>> palindromes(n);
  Trie trie;

  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    trie.insert(s, i);
    palindromes[i] = make_pair(count_palindrome_substrings(s), i + 1);
    palindromes_at[palindromes[i]].push_back(i);
  }

  vector<vector<pair<int, int>>> queries_at_l(n);

  for (int qi = 0; qi < q; qi++) {
    string a, b;
    cin >> a >> b;

    int ia = trie.find(a);
    int ib = trie.find(b);
    if (ia > ib) swap(a, b), swap(ia, ib);

    queries_at_l[ia].push_back({ib, qi});
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}