#include <bits/stdc++.h>
using namespace std;

/*
map<tuple<int, int, vector<pair<int, int>>>, int> grundy;

int Grundy(int a, int b, vector<pair<int, int>> e) {
  if (grundy.find({a, b, e}) != grundy.end()) {
    return grundy[{a, b, e}];
  }

  if (a == 0 and b == 0) {
    return grundy[{a, b, e}] = 0;
  }

  set<int> g;

  for (int i = 0; i < (int)e.size(); i++) {
    vector<pair<int, int>> _e = e;
    _e.erase(_e.begin() + i);
    g.insert(Grundy(a, b, _e));
  }

  for (int i = 0; i < a; i++) {
    vector<pair<int, int>> _e;
    for (auto E : e) {
      if (E.first != i) {
        if (E.first > i) E.first--;
        _e.push_back(E);
      }
    }
    g.insert(Grundy(a - 1, b, _e));
  }

  for (int i = 0; i < b; i++) {
    vector<pair<int, int>> _e;
    for (auto E : e) {
      if (E.second != i) {
        if (E.second > i) E.second--;
        _e.push_back(E);
      }
    }
    g.insert(Grundy(a, b - 1, _e));
  }

  int i = 0;
  for (auto it = g.begin(); it != g.end(); it++, i++) {
    if (*it != i) break;
  }

  // debug() << name(a) name(b) name(e) name(i);
  // assert((i > 0) == (e % 2 == 0));

  return grundy[{a, b, e}] = i;
}

void go(int a, int b) {
  grundy.clear();

  vector<pair<int, int>> e;
  for (int i = 0; i < a; i++) {
    for (int j = 0; j < b; j++) {
      e.push_back({i, j});
    }
  }
  Grundy(a, b, e);

  vector<vector<map<int, int>>> freq(
      a + 1, vector<map<int, int>>(b + 1));
  for (auto [key, g] : grundy) {
    auto [_a, _b, e] = key;
    freq[_a][_b][g]++;
  }

  for (int _a = 0; _a <= a; _a++) {
    for (int _b = 0; _b <= b; _b++) {
      debug() << name(_a) name(_b) name(freq[_a][_b]);
    }
  }
}
*/

typedef long long ll;
const int MOD = 1e9 + 7;
const int N = 1e5 + 5;

ll inv[N], fact[N], ifact[N];

ll binExp(ll a, ll e, ll m = MOD) {
  if (e == -1) {
    e = m - 2;
  }
  ll ret = 1;
  while (e) {
    if (e & 1) {
      ret = ret * a % m;
    }
    a = a * a % m, e >>= 1;
  }
  return ret;
}

int main() {
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

  int n;
  cin >> n;

  vector<pair<int, int>> v;
  for (int i = 0; i < n; i++) {
    int a, b;
    scanf("%d %d", &a, &b);
    v.emplace_back(a, b);
  }

  long long cnt[2] = {0, 0};
  long long mult[2] = {1, 1};
  for (auto [a, b] : v) {
    cnt[(a + b) % 2]++;
    (mult[(a + b) % 2] *= binExp(2, (long long)a * b - 1)) %= MOD;
  }

  if (cnt[1] % 2 == 1 or cnt[1] / 2 > cnt[0]) {
    puts("0");
  } else {
    ll ans = mult[0] * mult[1] % MOD;
    (ans *= fact[cnt[1]] * ifact[cnt[1] / 2] % MOD * ifact[cnt[1] / 2]
            % MOD) %= MOD;
    (ans *= fact[cnt[0]] * ifact[cnt[1] / 2] % MOD
            * ifact[cnt[0] - cnt[1] / 2] % MOD) %= MOD;
    cout << ans << endl;
  }

  return 0;
}