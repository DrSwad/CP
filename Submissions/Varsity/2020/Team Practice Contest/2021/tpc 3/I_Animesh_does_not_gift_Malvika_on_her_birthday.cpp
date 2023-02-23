#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 55;
const int MOD = 1e9 + 7;
const int INV2 = (MOD + 1) / 2;

int n;
ll C[N][N];
ll perm[N];
vector<int> adj[N];
int cycles[N], lines[N];
bool vis[N];

void reset() {
  for (int i = 1; i < N; i++) adj[i].clear();
  memset(cycles, 0, sizeof cycles);
  memset(lines, 0, sizeof lines);
  memset(vis, false, sizeof vis);
}

int dfs(int at) {
  if (vis[at]) return 0;
  vis[at] = true;

  int ret = 1;
  for (int to : adj[at]) {
    ret += dfs(to);
  }

  return ret;
}

int main() {
  int t;
  cin >> t;

  for (int i = 0; i < N; i++) {
    C[i][0] = C[i][i] = 1;
    for (int j = 1; j < i; j++) {
      C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
    }
  }

  perm[0] = 1;
  for (int i = 1; i < N; i++) {
    perm[i] = perm[i - 1] * i % MOD;
  }

  while (t--) {
    reset();

    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        char c;
        scanf(" %c", &c);
        if (i != j and c == '0') {
          adj[i].push_back(j);
        }
      }
    }

    for (int i = 1; i <= n; i++) {
      if (!vis[i] and adj[i].size() == 1) {
        lines[dfs(i)]++;
      }
    }

    for (int i = 1; i <= n; i++) {
      if (!vis[i] and !adj[i].empty()) {
        cycles[dfs(i)]++;
      }
    }

    int rem = n;
    ll ans = 1;

    for (int i = 1; i <= n; i++) {
      if (lines[i]) {
        int take = i * lines[i];
        (ans *= C[rem][take]) %= MOD;
        rem -= take;

        for (int j = 0; j < lines[i]; j++) {
          (ans *= C[take - i * j - 1][i - 1] * perm[i] % MOD * INV2 % MOD) %= MOD;
        }
      }
      if (cycles[i]) {
        int take = i * cycles[i];
        (ans *= C[rem][take]) %= MOD;
        rem -= take;

        for (int j = 0; j < cycles[i]; j++) {
          (ans *= C[take - i * j - 1][i - 1] * perm[i - 1] % MOD * INV2 % MOD) %= MOD;
        }
      }
    }

    printf("%lld\n", ans);
  }

  return 0;
}