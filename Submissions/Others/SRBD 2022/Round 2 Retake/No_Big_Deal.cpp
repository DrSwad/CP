#include <bits/stdc++.h>
using namespace std;

// 1 2 3 ... k
// S (1) (2) (3) ... (k-1)
// k S 1 2 ... (k-2)
// k-1 k S 1 2 ... k-3
// 3 ... S 1
// 2 3 ... S
// 1 2 3 ... S

typedef long long ll;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int k;
  cin >> k;

  vector<ll> a(k);
  for (ll &i : a) cin >> i;

  ll s = 0;
  for (int i : a) s ^= i;

  vector<ll> p(k + 1);
  p[0] = a[0];
  for (int i = 1; i < k; i++) {
    p[i] = p[i - 1] ^ a[i];
  }
  p[k] = 0;

  function<ll(ll)> pref = [&](ll i) {
    return p[i % (k + 1)];
  };

  int q;
  cin >> q;

  while (q--) {
    ll l, r;
    cin >> l >> r;
    l--, r--;
    cout << (pref(r) ^ (l ? pref(l - 1) : 0)) << "\n";
  }

  return 0;
}