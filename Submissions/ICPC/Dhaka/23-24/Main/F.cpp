#include <bits/stdc++.h>

using namespace std;

const int LG = 31;
const int N = 200010;
const int MOD = 1e9 + 7;

struct VectorSpace {
  vector<int> basis;

  VectorSpace() : basis(LG, 0) {}

  void insert(int x) {
    for (int i = LG - 1; i >= 0; --i) if (x & 1 << i) {
        if (basis[i]) x ^= basis[i];
        else {basis[i] = x; break;}
      }
  }

  void normalize() {
    for (int i = LG - 1; i >= 0; --i) if (basis[i]) {
        for (int j = i + 1; j < LG; ++j) if (basis[j] & 1 << i) {
            basis[j] ^= basis[i];
          }
      }
  }
};

int two[N];

int main() {
  two[0] = 1;
  for (int i = 1; i < N; ++i) two[i] = 2LL * two[i - 1] % MOD;
  int t, cases = 0;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (int &x : a) scanf("%d", &x);
    for (int &x : b) scanf("%d", &x);
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end()), m = b.size();
    VectorSpace bigSpace;
    for (int &x : a) bigSpace.insert(x);
    int ans = 0;
    // for (int i = 0; i < LG; ++i) if (bigSpace.basis[i]) cerr << bigSpace.basis[i] << " "; cerr << '\n';
    for (int mask = 0; mask < 1 << m; ++mask) {
      int required = 0;
      for (int i = 0; i < m; ++i) if (mask & 1 << i) required |= b[i];
      VectorSpace smallSpace;
      for (int i = 0; i < LG; ++i) {
        int here = bigSpace.basis[i];
        if (here) smallSpace.insert(here & required);
      }
      smallSpace.normalize();
      // for (int i = 0; i < LG; ++i) if (smallSpace.basis[i]) cerr << smallSpace.basis[i] << " --- "; cerr << '\n';
      int rank = 0, united = required;
      for (int i = 0; i < LG; ++i) if (smallSpace.basis[i]) ++rank, united ^= smallSpace.basis[i];
      if (united) continue;
      int here = two[n - rank];
      // cerr << bitset<2>(mask) << " --> " << here << '\n';
      // if (!rank) {
      //   here += MOD - 1;
      //   if (here >= MOD) here -= MOD;
      // }
      // cerr << here << '\n';
      if (__builtin_parity(mask)) {
        ans -= here;
        if (ans < 0) ans += MOD;
      } else {
        ans += here;
        if (ans >= MOD) ans -= MOD;
      }
    }
    // cerr << ans << '\n';
    if (b[0]) {
      ans += MOD - 1;
      if (ans >= MOD) ans -= MOD;
    }
    printf("Case %d: %d\n", ++cases, ans);
  }
  return 0;
}