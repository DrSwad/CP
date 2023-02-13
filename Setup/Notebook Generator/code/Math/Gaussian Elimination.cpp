#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

const int N = 505;
const ld EPS = 1e-10;
const int MOD = 998244353;

ll bigMod (ll a, ll e, ll mod) {
  if (e == -1) e = mod - 2;
  ll ret = 1;
  while (e) {
    if (e & 1) ret = ret * a % mod;
    a = a * a % mod, e >>= 1;
  }
  return ret;
}

pair <int, ld> gaussJordan (int n, int m, ld eq[N][N], ld res[N]) {
  ld det = 1;
  vector <int> pos(m, -1);
  for (int i = 0, j = 0; i < n and j < m; ++j) {
    int piv = i;
    for (int k = i; k < n; ++k) if (fabs(eq[k][j]) > fabs(eq[piv][j])) piv = k;
    if (fabs(eq[piv][j]) < EPS) continue; pos[j] = i;
    for (int k = j; k <= m; ++k) swap(eq[piv][k], eq[i][k]);
    if (piv ^ i) det = -det; det *= eq[i][j];
    for (int k = 0; k < n; ++k) if (k ^ i) {
      ld x = eq[k][j] / eq[i][j];
      for (int l = j; l <= m; ++l) eq[k][l] -= x * eq[i][l];
    } ++i;
  }
  int free_var = 0;
  for (int i = 0; i < m; ++i) {
    pos[i] == -1 ? ++free_var, res[i] = det = 0 : res[i] = eq[pos[i]][m] / eq[pos[i]][i];
  }
  for (int i = 0; i < n; ++i) {
    ld cur = -eq[i][m];
    for (int j = 0; j < m; ++j) cur += eq[i][j] * res[j];
    if (fabs(cur) > EPS) return make_pair(-1, det);
  }
  return make_pair(free_var, det);
}

pair <int, int> gaussJordanModulo (int n, int m, int eq[N][N], int res[N], int mod) {
  int det = 1;
  vector <int> pos(m, -1); 
  const ll mod_sq = (ll) mod * mod;
  for (int i = 0, j = 0; i < n and j < m; ++j) {
    int piv = i;
    for (int k = i; k < n; ++k) if (eq[k][j] > eq[piv][j]) piv = k;
    if (!eq[piv][j]) continue; pos[j] = i;
    for (int k = j; k <= m; ++k) swap(eq[piv][k], eq[i][k]);
    if (piv ^ i) det = det ? MOD - det : 0; det = (ll) det * eq[i][j] % MOD;
    for (int k = 0; k < n; ++k) if (k ^ i and eq[k][j]) {
      ll x = eq[k][j] * bigMod(eq[i][j], -1, mod) % mod;
      for (int l = j; l <= m; ++l) if (eq[i][l]) eq[k][l] = (eq[k][l] + mod_sq - x * eq[i][l]) % mod;
    } ++i;
  }
  int free_var = 0;
  for (int i = 0; i < m; ++i) {
    pos[i] == -1 ? ++free_var, res[i] = det = 0 : res[i] = eq[pos[i]][m] * bigMod(eq[pos[i]][i], -1, mod) % mod;
  }
  for (int i = 0; i < n; ++i) {
    ll cur = -eq[i][m];
    for (int j = 0; j < m; ++j) cur += (ll) eq[i][j] * res[j], cur %= mod;
    if (cur) return make_pair(-1, det);
  }
  return make_pair(free_var, det);
}

pair <int, int> gaussJordanBit (int n, int m, bitset <N> eq[N], bitset <N> &res) {
  int det = 1;
  vector <int> pos(m, -1); 
  for (int i = 0, j = 0; i < n and j < m; ++j) {
    int piv = i;
    for (int k = i; k < n; ++k) if (eq[k][j]) {
      piv = k; break;
    }
    if (!eq[piv][j]) continue; pos[j] = i, swap(eq[piv], eq[i]), det &= eq[i][j];
    for (int k = 0; k < n; ++k) if (k ^ i and eq[k][j]) eq[k] ^= eq[i]; ++i;
  }
  int free_var = 0;
  for (int i = 0; i < m; ++i) {
    pos[i] == -1 ? ++free_var, res[i] = det = 0 : res[i] = eq[pos[i]][m];
  }
  for (int i = 0; i < n; ++i) {
    int cur = eq[i][m];
    for (int j = 0; j < m; ++j) cur ^= eq[i][j] & res[j];
    if (cur) return make_pair(-1, det);
  }
  return make_pair(free_var, det); 
}

int main() {
  
  return 0;
}

