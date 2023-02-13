#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e5 + 5;
const int MOD = 1e9 + 7;

int n;
int v[N];
ll fact[N], ifact[N], inv[N];
int par[N], sub[N];
vector<int> e[N];
ll dp[N];

void reset() {
  for (int i = 1; i <= n; i++) {
    par[i] = 0;
    e[i].clear();
  }
}

ll nCk(int n, int k) {
  if (k<0 or k> n) return 0;
  return fact[n] * ifact[k] % MOD * ifact[n - k] % MOD;
}

void init() {
  inv[1] = fact[0] = ifact[0] = 1;
  for (int i = 2; i < N; i++) inv[i] = (ll)inv[MOD % i] * (MOD - MOD / i) % MOD;
  for (int i = 1; i < N; i++) fact[i] = (ll)fact[i - 1] * i % MOD;
  for (int i = 1; i < N; i++) ifact[i] = (ll)ifact[i - 1] * inv[i] % MOD;
}

int initTree() {
  vector<int> st;
  for (int i = 1; i <= n; i++) {
    if (v[i] > st.size() + 1) return 0;

    if (v[i] > 1) par[i] = st[v[i] - 2];
    if (v[i] < st.size() + 1) par[st[v[i] - 1]] = i;

    st.resize(v[i] - 1);
    st.push_back(i);
  }

  int root = 0;
  for (int i = 1; i <= n; i++) {
    if (!par[i]) {
      assert(!root);
      root = i;
    }
    else {
      e[par[i]].push_back(i);
    }
  }
  assert(root);

  return root;
}

void dfs(int at) {
  sub[at] = 1;
  for (int to : e[at]) {
    dfs(to);
    sub[at] += sub[to];
  }

  dp[at] = 1;
  int rem = sub[at] - 1;
  for (int to : e[at]) {
    (dp[at] *= nCk(rem, sub[to]) * dp[to] % MOD) %= MOD;
    rem -= sub[to];
  }
}

int main() {
  init();

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    printf("Case #%d: ", cs);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &v[i]);

    int root = initTree();
    if (!root) puts("0");
    else {
      dfs(root);
      printf("%lld\n", dp[root]);
    }

    reset();
  }

  return 0;
}