#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int mod = 998244353;
const int bits = 30;

ll binExp(ll a, ll e, ll m = mod) {
  if (e == -1) e = m - 2;
  ll ret = 1;
  while (e) {
    if (e & 1) ret = ret * a % m;
    a = a * a % m, e >>= 1;
  }
  return ret;
}

int add(int a, int b) {
  int c = a + b;
  return c < mod ? c : c - mod;
}

int mul(int a, int b) {
  return 1ll * a * b % mod;
}

struct Trie {
  const int A = 2;
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

  inline void insert(int a) {
    int cur = 0;
    cnt[cur]++;
    for (int i = bits - 1; i >= 0; i--) {
      int to = a >> i & 1;
      if (next[cur][to] == -1) next[cur][to] = node();
      cur = next[cur][to];
      cnt[cur]++;
    }
  }

  int dfs(int at, int cnt1) {
    int ret = 0;

    int left = next[at][0] == -1 ? 0 : cnt[next[at][0]];
    int right = next[at][1] == -1 ? 0 : cnt[next[at][1]];
    if (left == 0 and right == 0) {
      ret = mul(cnt1 + 1, mul(cnt[at], cnt[at]));
    }
    else {
      ret = mul((cnt1 + 1) + (cnt1 + 2), mul(left, right));
      if (next[at][0] != -1) ret = add(ret, dfs(next[at][0], cnt1));
      if (next[at][1] != -1) ret = add(ret, dfs(next[at][1], cnt1 + 1));
    }

    return ret;
  }
};

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  Trie trie;
  for (int i : a) trie.insert(i);

  cout << mul(trie.dfs(0, 0), binExp(1ll * n * n % mod, -1)) << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}