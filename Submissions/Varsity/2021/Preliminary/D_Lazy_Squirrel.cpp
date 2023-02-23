#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e6 + 5;
const int MOD = int(1e9) + 7;
const ll P[] = {97, 1000003};

ll pwr[2][N];

void initHash() {
  for (int it = 0; it < 2; ++it) {
    pwr[it][0] = 1;
    for (int i = 1; i < N; ++i) {
      pwr[it][i] = pwr[it][i - 1] * P[it] % MOD;
    }
  }
}

void push_char(char c, int len, ll &hash_val, ll &rev_hash_val) {
  ll mask = ((1ll << 30) - 1);
  ll h[2] = {hash_val &mask, hash_val >> 30};
  ll rev[2] = {rev_hash_val &mask, rev_hash_val >> 30};
  for (int it = 0; it < 2; ++it) {
    h[it] = (h[it] + pwr[it][len] * (c + 1)) % MOD;
    rev[it] = (rev[it] * P[it] + P[it] * (c + 1)) % MOD;
  }
  hash_val = (h[1] << 30) + h[0];
  rev_hash_val = (rev[1] << 30) + rev[0];
}

void test_case() {
  int n;
  cin >> n;

  string s;
  cin >> s;

  vector<vector<int>> e(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    e[u].push_back(v);
    e[v].push_back(u);
  }

  int up = 0;
  function<void(int, int, int, ll, ll)> dfs = [&](int at, int from, int depth, ll hash_val, ll rev_hash_val) {
    push_char(s[at], depth + 1, hash_val, rev_hash_val);
    up += hash_val == rev_hash_val;
    for (int to : e[at]) {
      if (to != from) {
        dfs(to, at, depth + 1, hash_val, rev_hash_val);
      }
    }
  };
  dfs(0, -1, 0, 0ll, 0ll);

  int down = n;
  int g = __gcd(up, down);
  up /= g;
  down /= g;

  cout << up << "/" << down << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  initHash();

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}