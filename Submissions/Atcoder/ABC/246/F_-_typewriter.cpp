#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MOD = 998244353;

ll binExp(ll a, ll e, ll m = MOD) {
  if (e == -1) e = m - 2;
  ll ret = 1;
  while (e) {
    if (e & 1) ret = ret * a % m;
    a = a * a % m, e >>= 1;
  }
  return ret;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, l;
  cin >> n >> l;

  vector<string> s(n);
  for (string &ss : s) cin >> ss;

  vector<bitset<26>> vis(n);
  for (int i = 0; i < n; i++) {
    for (char c : s[i]) {
      vis[i][c - 'a'] = true;
    }
  }

  vector<int> power(27);
  for (int i = 0; i < 27; i++) {
    power[i] = binExp(i, l);
  }

  ll ans = 0;

  for (int mask = 1; mask < 1 << n; mask++) {
    bitset<26> inter(-1);
    for (int i = 0; i < n; i++) {
      if (mask >> i & 1) inter &= vis[i];
    }

    int cnt = inter.count();

    if (__builtin_popcount(mask) % 2 == 1) {
      (ans += power[cnt]) %= MOD;
    }
    else {
      (ans += MOD - power[cnt]) %= MOD;
    }
  }

  cout << ans << "\n";

  return 0;
}