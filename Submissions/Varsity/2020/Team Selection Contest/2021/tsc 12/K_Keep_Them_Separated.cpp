#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 2.5e3 + 5;
const int MOD = 1e9 + 9;
const int BASE = 62843673;

static random_device rd;
static mt19937 rng(rd());
uniform_int_distribution<int> uid(1, MOD - 1);

ll f[N][N];
void update(int p, int q, ll v) {
  while (p < N) {
    int _q = q;
    while (_q < N) { (f[p][_q] += v) %= MOD, _q += _q & -_q; }
    p += p & -p;
  }
}
ll pref(int p, int q) {
  ll ret = 0;
  while (p) {
    int _q = q;
    while (_q) { (ret += f[p][_q]) %= MOD, _q -= _q & -_q; }
    p -= p & -p;
  }
  return ret;
}

void processRect(int x1, int y1, int x2, int y2, ll hashVal) {
  ll _hashVal = (MOD - hashVal);
  update(min(x1, x2), min(y1, y2), hashVal);
  update(min(x1, x2), max(y1, y2), _hashVal);
  update(max(x1, x2), min(y1, y2), _hashVal);
  update(max(x1, x2), max(y1, y2), hashVal);
}

ll getCell(int x, int y) {
  ll ret = pref(x, y) - pref(x - 1, y) - pref(x, y - 1)
      + pref(x - 1, y - 1);
  ret = (MOD + ret % MOD) % MOD;
  return ret;
}

int main() {
  int q;
  cin >> q;

  ll currPow = BASE;
  vector<tuple<int, int, int, int, ll>> qRects;

  while (q--) {
    int type;
    scanf("%d", &type);

    if (type == 1) {
      ll newHash = currPow * uid(rng) % MOD;
      (currPow *= BASE) %= MOD;

      int x1, y1, x2, y2;
      scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
      (x1 += 1) >>= 1;
      (y1 += 1) >>= 1;
      (x2 += 1) >>= 1;
      (y2 += 1) >>= 1;

      processRect(x1, y1, x2, y2, newHash);
      qRects.emplace_back(x1, y1, x2, y2, newHash);
    } else {
      qRects.emplace_back(0, 0, 0, 0, 0);
    }

    if (type == 2) {
      int j;
      scanf("%d", &j);
      auto [x1, y1, x2, y2, hashVal] = qRects[j - 1];
      processRect(x1, y1, x2, y2, MOD - hashVal);
    }

    if (type == 3) {
      int x1, y1, x2, y2;
      scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
      x1 >>= 1;
      y1 >>= 1;
      x2 >>= 1;
      y2 >>= 1;

      ll q1 = pref(x1, y1);
      ll q2 = pref(x2, y2);
      // debug() << name(x1) name(y1) name(q1) name(x2) name(y2)
      //         name(q2);
      printf("%c", q1 == q2 ? 'Y' : 'N');
    }

    // for (int r = 1; r < 10; r++) {
    //   for (int c = 1; c < 10; c++) { cerr << getCell(r, c) << " ";
    //   } cerr << endl;
    // }
    // cerr << endl;
  }

  puts("");

  return 0;
}