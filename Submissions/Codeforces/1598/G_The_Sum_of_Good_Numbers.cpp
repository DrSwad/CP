#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int HN = 2;
const int mod[HN] = {97, 1000003};
typedef array<ll, HN> hval;
const int B = 10;
const int N = 5e5 + 5;

ll bigMod(ll a, ll e, ll mod) {
  if (e == -1) e = mod - 2;
  ll ret = 1;
  while (e) {
    if (e & 1) ret = ret * a % mod;
    a = a * a % mod, e >>= 1;
  }
  return ret;
}

ll pwr[HN][N], inv[HN][N];

void initHash() {
  for (int it = 0; it < HN; ++it) {
    pwr[it][0] = inv[it][0] = 1;
    ll INV_B = bigMod(B, -1, mod[it]);
    for (int i = 1; i < N; ++i) {
      pwr[it][i] = pwr[it][i - 1] * B % mod[it];
      inv[it][i] = inv[it][i - 1] * INV_B % mod[it];
    }
  }
}

hval add(const hval &h1, const hval &h2) {
  hval ret = h1;
  for (int it = 0; it < HN; it++) {
    ret[it] += h2[it];
    if (ret[it] >= mod[it]) ret[it] -= mod[it];
  }
  return ret;
}

hval sub(const hval &h1, const hval &h2) {
  hval ret = h1;
  for (int it = 0; it < HN; it++) {
    ret[it] -= h2[it];
    if (ret[it] < 0) ret[it] += mod[it];
  }
  return ret;
}

struct RangeHash {
  vector<ll> h[HN];

  RangeHash(const string S) {
    for (int it = 0; it < HN; ++it) {
      h[it].resize(S.size() + 1, 0);
      for (int i = 0; i < S.size(); ++i) {
        h[it][i + 1] = (h[it][i] + pwr[it][i + 1] * (S[i] - '0')) % mod[it];
      }
    }
  }

  inline hval get(int l, int r) {
    hval ret;
    for (int it = 0; it < HN; it++) {
      ret[it] = (h[it][r + 1] - h[it][l] + mod[it]) * inv[it][l + 1] % mod[it];
    }
    return ret;
  }
};

string s, x;
map<hval, int> mn, mx;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  initHash();

  cin >> s;
  int nn = s.length();
  reverse(s.begin(), s.end());
  RangeHash sh(s);

  string x;
  cin >> x;
  reverse(x.begin(), x.end());
  RangeHash xh(x);
  hval xx = xh.get(0, (int)x.length() - 1);

  mn[hval{0}] = mx[hval{0}] = -1;
  for (int i = 0; i < nn; i++) {
    hval h = sh.get(0, i);
    if (mn.find(h) == mn.end()) mn[h] = i;
    mx[h] = i;
  }
  debug(mn);
  debug(mx);

  for (int it = 0; it < 2; it++) {
    int len = (int)x.length() - it;
    if (len <= 0) continue;

    for (int l = 0; l + len - 1 < nn; l++) {
      int r = l + len - 1;

      hval ss = sh.get(l, r);
      hval need = sub(xx, ss);
      if (l > 0) {
        hval needL = sub(sh.get(0, l - 1), need);
        if (mn.find(needL) != mn.end() and mn[needL] < l - 1) {
          cout << (nn + 1) - (l) << " " << (nn + 1) - (mn[needL] + 2) << "\n";
          cout << (nn + 1) - (r + 1) << " " << (nn + 1) - (l + 1) << "\n";
          return 0;
        }
      }
      if (r < nn - 1) {
        hval needR = add(sh.get(0, r), need);
        if (mn.find(needR) != mn.end() and mn[needR] > r) {
          cout << (nn + 1) - (r + 1) << " " << (nn + 1) - (l + 1) << "\n";
          cout << (nn + 1) - (mn[needR] + 1) << " " << (nn + 1) - (r + 2) << "\n";
          return 0;
        }
      }
    }
  }

  return 0;
}