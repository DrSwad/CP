#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
struct chash {
  const int RANDOM = (long long)(make_unique<char>().get())
                     ^ chrono::high_resolution_clock::now()
                     .time_since_epoch()
                     .count();
  static unsigned long long hash_f(unsigned long long x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
  static unsigned hash_combine(unsigned a, unsigned b) {
    return a * 31 + b;
  }
  int operator()(int x) const { return hash_f(x) ^ RANDOM; }
  int operator()(pair<int, int> x) const {
    return hash_combine(x.first, x.second) ^ RANDOM;
  }
};

typedef long long ll;

const int N = 3e5 + 5;
const int MOD = int(1e9) + 7;

const ll P[] = {97, 1000003};

ll bigMod(ll a, ll e) {
  if (e == -1) e = MOD - 2;
  ll ret = 1;
  while (e) {
    if (e & 1) ret = ret * a % MOD;
    a = a * a % MOD, e >>= 1;
  }
  return ret;
}

ll pwr[2][N], inv[2][N];

void initHash() {
  for (int it = 0; it < 2; ++it) {
    pwr[it][0] = inv[it][0] = 1;
    ll INV_P = bigMod(P[it], -1);
    for (int i = 1; i < N; ++i) {
      pwr[it][i] = pwr[it][i - 1] * P[it] % MOD;
      inv[it][i] = inv[it][i - 1] * INV_P % MOD;
    }
  }
}

int n;
string S;
vector<ll> h[2];

void calcHash() {
  for (int it = 0; it < 2; ++it) {
    h[it].resize(S.size() + 1, 0);
    for (int i = 0; i < S.size(); ++i) {
      h[it][i + 1] = (h[it][i] + pwr[it][i + 1] * (S[i] - 'a' + 1)) % MOD;
    }
  }
}

inline ll get(int l, int r) {
  ll one = (h[0][r + 1] - h[0][l]) * inv[0][l + 1] % MOD;
  ll two = (h[1][r + 1] - h[1][l]) * inv[1][l + 1] % MOD;
  if (one < 0) one += MOD; if (two < 0) two += MOD;
  return one << 31 | two;
}

int getAns(int len) {
  gp_hash_table<ll, int, chash> lastAt;
  vector<bool> valid(n - len + 1, true);

  for (int i = n - len; ~i; i--) {
    ll hashVal = get(i, i + (len - 1));

    if (lastAt.find(hashVal) != lastAt.end()) {
      valid[i] = valid[lastAt[hashVal]] = false;
    }

    lastAt[hashVal] = i;
  }

  for (int i = 0; i < valid.size(); i++) {
    if (valid[i]) return i;
  }

  return -1;
}

int main() {
  cin >> S;
  initHash();
  calcHash();

  n = S.length();
  int L = 1, R = n;

  while (L != R) {
    int M = (L + R) / 2;
    if (~getAns(M)) R = M;
    else L = M + 1;
  }

  cout << S.substr(getAns(L), L) << endl;

  return 0;
}