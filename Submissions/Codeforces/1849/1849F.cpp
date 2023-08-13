#include <bits/stdc++.h>
using namespace std;

const int B = 31;

struct Trie {
  const int A = 2;
  int N;
  vector<int> a;
  vector<vector<int>> next;
  vector<vector<int>> indices;

  Trie(vector<int> a) : N(0), a(a) {
    node();
    for (int i = 0; i < a.size(); i++) {
      insert(i, a[i]);
    }
  }

  int node() {
    next.emplace_back(A, -1);
    indices.emplace_back();
    return N++;
  }

  inline void insert(int index, int a) {
    int cur = 0;
    indices[cur].push_back(index);
    for (int i = B - 1; i >= 0; i--) {
      int to = a >> i & 1;
      if (next[cur][to] == -1) next[cur][to] = node();
      cur = next[cur][to];
      indices[cur].push_back(index);
    }
  }

  bool check_recursively(int at_node, int at_bit, int low_bound, vector<int> &s1, vector<int> &s2) {
    if (at_node == -1) return true;

    if (at_bit == -1) {
      assert(indices[at_node].size() == 1);
      s1.push_back(indices[at_node][0]);
      return true;
    }

    if (low_bound >> at_bit & 1) {
      int l = next[at_node][0];
      int r = next[at_node][1];

      vector<int> vl, vr;
      if (l != -1) vl = indices[l];
      if (r != -1) vr = indices[r];

      if (vl.size() > 2 or vr.size() > 2) return false;

      for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
          if (i < vl.size() and j < vr.size() and (a[vl[i]] ^ a[vr[j]]) < low_bound) continue;
          if ((i ^ 1) < vl.size() and (j ^ 1) < vr.size() and (a[vl[i ^ 1]] ^ a[vr[j ^ 1]]) < low_bound) continue;

          if (i < vl.size()) s1.push_back(vl[i]);
          if ((i ^ 1) < vl.size()) s2.push_back(vl[i ^ 1]);
          if (j < vr.size()) s1.push_back(vr[j]);
          if ((j ^ 1) < vr.size()) s2.push_back(vr[j ^ 1]);

          return true;
        }
      }

      return false;
    }
    else {
      return check_recursively(next[at_node][0], at_bit - 1, low_bound, s1, s2) and
             check_recursively(next[at_node][1], at_bit - 1, low_bound, s1, s2);
    }
  }

  bool check(int low_bound, string &s) {
    vector<int> s1, s2;
    if (!check_recursively(0, B - 1, low_bound, s1, s2)) return false;
    for (int i : s1) s[i] = '0';
    for (int i : s2) s[i] = '1';
    return true;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  Trie trie(a);

  int L = 0, R = (1 << (B - 1)) + 1;
  string s(n, '0');
  while (R - L > 1) {
    string ss(n, '0');
    int mid = ((long long)L + R) / 2;
    if (trie.check(mid, ss)) L = mid, swap(s, ss);
    else R = mid;
  }

  cout << s << "\n";

  return 0;
}