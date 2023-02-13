#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int B = 31;
const int MOD = 1e9 + 7;

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

  void insert(int a) {
    int cur = 0;
    for (int b = B - 1; b >= 0; b--) {
      cnt[cur]++;
      int to = a >> b & 1;
      if (next[cur][to] == -1) next[cur][to] = node();
      cur = next[cur][to];
    }
    cnt[cur]++;
  }

  int find_max(int x) {
    int ret = 0;
    int cur = 0;
    for (int b = B - 1; b >= 0; b--) {
      int to = (x >> b & 1) ^ 1;
      if (next[cur][to] == -1 or cnt[next[cur][to]] == 0) to ^= 1;
      ret = ret * 2 + to;
      cur = next[cur][to];
      assert(cur != -1);
    }
    return ret;
  }

  void erase(int a) {
    int cur = 0;
    for (int b = B - 1; b >= 0; b--) {
      cnt[cur]--;
      int to = a >> b & 1;
      cur = next[cur][to];
    }
    cnt[cur]--;
  }
};

ll binExp(ll a, ll e, ll m = MOD) {
  if (e == -1) e = m - 2;
  ll ret = 1;
  while (e) {
    if (e & 1) ret = ret * a % m;
    a = a * a % m, e >>= 1;
  }
  return ret;
}

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<vector<int>> adj(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  Trie trie;
  int ans = 0;

  function<void(int, int, int, int)> dfs = [&](int at, int from, int weight, int x) {
    // DB();
    int children = 0;
    for (int to : adj[at]) {
      if (to != from) children++;
    }

    trie.insert(a[at]);
    x ^= a[at];

    // debug(at, from, weight, x);

    if (children) {
      weight = 1ll * weight * binExp(children, -1) % MOD;
      for (int to : adj[at]) {
        if (to != from) dfs(to, at, weight, x);
      }
    }
    else {
      // debug(at, x, trie.find_max(x));
      (ans += 1ll * (x ^ trie.find_max(x)) * weight % MOD) %= MOD;
    }

    trie.erase(a[at]);
  };

  dfs(0, -1, 1, 0);

  cout << ans << "\n";
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