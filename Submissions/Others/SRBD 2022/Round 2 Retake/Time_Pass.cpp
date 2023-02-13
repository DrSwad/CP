#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

class BIT {
public:
  int n;
  vector<ll> f;
  BIT(int n) : n(n) {
    f.resize(n + 1, 0ll);
  }
  void update(int p, int v) {
    while (p <= n) f[p] += v, p += p & -p;
  }
  ll pref(int p) {
    ll ret = 0;
    while (p) ret += f[p], p -= p & -p;
    return ret;
  }
};

const int N = 1e6 + 5;
const int LOGN = 20;
int freq[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  BIT bit_sum(N);
  BIT bit_freq(N);

  int type;
  while (cin >> type, type != -1) {
    if (type == 1) {
      int n;
      cin >> n;
      freq[n]++;
      bit_freq.update(n, 1);
      bit_sum.update(n, n);
    }
    else if (type == 2) {
      int m;
      cin >> m;
      if (freq[m] == 0) {
        cout << "-1\n";
      }
      else {
        cout << m << "\n";
        freq[m]--;
        bit_freq.update(m, -1);
        bit_sum.update(m, -m);
      }
    }
    else if (type == 3) {
      int k;
      cin >> k;

      int pos = 0;
      for (int i = LOGN - 1; i >= 0; i--) {
        int npos = pos + (1 << i);
        if (npos < N and bit_freq.pref(npos) < k) pos = npos;
      }

      int found = bit_freq.pref(pos), rem = k - found;
      cout << bit_sum.pref(pos) + (ll)(pos + 1) * rem << "\n";
    }
  }

  return 0;
}