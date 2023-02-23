#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 1e9 + 9;
const int BASE = 6827923;
const int N = 1e6 + 5;

int pow_base[N];
ll inv[N], fact[N], ifact[N];

int main() {
  pow_base[0] = 1;
  for (int i = 1; i < N; i++) {
    pow_base[i] = (ll)pow_base[i - 1] * BASE % MOD;
  }

  int n, m, k;
  cin >> n >> m >> k;

  vector<int> a(n), b(n);
  vector<ll> da(n), db(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
    a[i] %= m;
  }
  for (int i = 0; i < n; i++) {
    scanf("%d", &b[i]);
    b[i] %= m;
  }
  for (int i = 0; i < n; i++) {
    int j = (i + 1) % n;
    da[i] = (a[j] - a[i] + m) % m;
  }
  for (int i = 0; i < n; i++) {
    int j = (i + 1) % n;
    db[i] = (b[i] - b[j] + m) % m;
  }

  ll hashA = 0, hashB = 0;
  for (int i = 0; i < n; i++) {
    (hashA += da[i] * pow_base[i + 1] % MOD) %= MOD;
  }
  for (int i = 0; i < n; i++) {
    (hashB += db[i] * pow_base[i + 1] % MOD) %= MOD;
  }
  debug() << name(hashA) name(hashB);

  bool curMatch = hashA == hashB;
  int matchCnt = 0;
  int i = 0;
  do {
    debug() << name(i);
    i = (i - 1 + n) % n;
    (hashB *= BASE) %= MOD;
    (hashB += db[i] * pow_base[1] % MOD) %= MOD;
    (hashB += (ll)MOD - db[i] * pow_base[n + 1] % MOD) %= MOD;
    matchCnt += hashB == hashA;
    debug() << name(hashB);
  } while (i);

  matchCnt -= curMatch;

  inv[1] = fact[0] = ifact[0] = 1;
  for (int i = 2; i < N; i++) {
    inv[i] = (ll)inv[MOD % i] * (MOD - MOD / i) % MOD;
  }
  for (int i = 1; i < N; i++) {
    fact[i] = (ll)fact[i - 1] * i % MOD;
  }
  for (int i = 1; i < N; i++) {
    ifact[i] = (ll)ifact[i - 1] * inv[i] % MOD;
  }

  if (k > n) {
    puts("0");
    return 0;
  }

  for (int i = 0; i < n; i++) {
    debug() << name(i) name(da[i]) name(db[i]);
  }
  debug() << name(curMatch) name(matchCnt);

  ll ans = 0;
  if (curMatch) {
    ll curr = 1;
    for (int i = 1; i <= k - 1; i++) {
      (curr *= (n - i)) %= MOD;
    }
    ans += curr;
  }
  if (matchCnt) {
    ll curr = matchCnt;
    for (int i = 1; i <= k - 1; i++) {
      (curr *= (n - i)) %= MOD;
    }
    if (k >= 2) {
      (curr *= inv[n - 1]) %= MOD;
      (curr *= n - 2) %= MOD;
    }
    ans += curr;
  }

  cout << ans << endl;

  return 0;
}