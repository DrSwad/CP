#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
const int MAX_H = 1e9;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;

  vector<ll> h(n + 1);
  for (ll &i : h) cin >> i;

  cout << fixed << setprecision(10);
  while (q--) {
    int a, b;
    char c;
    cin >> a >> c >> b;
    int g = a * 10 + (a < 0 ? -b : b);

    ld ans = 0;
    bool possible = false;

    for (int it = 0; it < 2; it++) {
      vector<ll> pref(n + 1);
      pref[0] = 0;
      for (int i = 1; i <= n; i++) {
        pref[i] = pref[i - 1] + (h[i] - h[i - 1] - g);
      }

      vector<int> pref_ordered(n + 1);
      iota(pref_ordered.begin(), pref_ordered.end(), 0);
      sort(
        pref_ordered.begin(),
        pref_ordered.end(),
        [&](int i, int j) {
        if (pref[i] != pref[j]) return pref[i] > pref[j];
        return i > j;
      }
        );

      int r = 0;
      for (int at : pref_ordered) {
        if (r > at) {
          ld curr = r - at;

          if (r < n) {
            ll diff = h[r + 1] - h[r] - g;
            assert(diff < 0);
            curr += min(1.0L, (ld)(pref[at] - pref[r]) / diff);
          }

          possible = true;
          ans = max(ans, curr);
        }

        r = max(r, at);
      }

      for (ll &i : h) i = MAX_H - i;
      reverse(h.begin(), h.end());
    }

    if (!possible and g <= 0) possible = true, ans = 0;
    if (!possible) cout << "impossible\n";
    else cout << ans << "\n";
  }

  return 0;
}