#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 1e9 + 7;
#define bitcount(n) ((n) < (1ll << 31) ? (31 - __builtin_clz(n)) + 1 : (31 - __builtin_clz((n) >> 31)) + 31 + 1)

void test_case() {
  int k;
  cin >> k;

  vector<string> colors = {"white", "yellow", "green", "blue", "red", "orange"};

  int n;
  cin >> n;

  map<ll, int> fixed;
  map<ll, vector<ll>> mdp;
  vector<ll> nodes(1, 1);

  while (n--) {
    ll id, col;
    string s;
    cin >> id >> s;
    col = find(colors.begin(), colors.end(), s) - colors.begin();

    fixed[id] = col;
    while (id > 1) {
      nodes.push_back(id);
      id /= 2;
    }
  }

  // height of node x -> bitcount(x)

  sort(nodes.begin(), nodes.end());
  nodes.resize(unique(nodes.begin(), nodes.end()) - nodes.begin());
  sort(nodes.begin(), nodes.end(), [&](ll i, ll j) {
    return bitcount(i) > bitcount(j);
  });

  vector<ll> dp(k);
  dp[0] = 1;
  for (int i = 1; i < k; i++) {
    dp[i] = 4ll * dp[i - 1] % MOD;
    dp[i] = dp[i] * dp[i] % MOD;
  }

  // dp index of node x -> k - bitcount(x)

  for (ll id : nodes) {
    int h = bitcount(id);

    if (h == k) {
      vector<ll> vdp(6, 0);
      if (fixed.find(id) != fixed.end()) {
        vdp[fixed[id]] = 1;
      }
      else {
        fill(vdp.begin(), vdp.end(), 1);
      }

      mdp[id] = vdp;
    }
    else {
      ll L = id << 1, R = id << 1 | 1;

      vector<ll> vdpL;
      if (mdp.find(L) != mdp.end()) vdpL = mdp[L];
      else vdpL.resize(6, dp[k - bitcount(L)]);

      vector<ll> vdpR;
      if (mdp.find(R) != mdp.end()) vdpR = mdp[R];
      else vdpR.resize(6, dp[k - bitcount(R)]);

      vector<ll> vdp(6, 0);
      for (int col = 0; col < 6; col++) {
        if (fixed.find(id) != fixed.end() and col != fixed[id]) continue;

        for (int colL = 0; colL < 6; colL++) {
          if (col == colL or (col ^ 1) == colL) continue;

          for (int colR = 0; colR < 6; colR++) {
            if (col == colR or (col ^ 1) == colR) continue;

            vdp[col] += vdpL[colL] * vdpR[colR] % MOD;
            if (vdp[col] >= MOD) vdp[col] -= MOD;
          }
        }
      }

      mdp[id] = vdp;
    }
  }

  ll ans = 0;
  for (int col = 0; col < 6; col++) {
    ans += mdp[1][col];
    if (ans >= MOD) ans -= MOD;
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  // cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}