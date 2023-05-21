#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = ll(2e9) + 5;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;

  vector<ll> a(n);
  for (ll &i : a) cin >> i;

  sort(a.begin(), a.end());

  auto check = [&](ll k, ll mn) {
    vector<ll> b = a;

    int inc_moves = min((ll)n, k);
    if ((k - inc_moves) & 1) inc_moves--;

    for (int i = 0; i < inc_moves; i++) {
      b[i] += k - i;
    }

    ll extra = 0;
    for (int i = 0; i < n; i++) {
      if (b[i] < mn) return false;
      extra += b[i] - mn;
    }

    return extra >= (k - inc_moves) / 2;
  };

  while (q--) {
    ll k;
    cin >> k;

    ll L = -INF, R = INF;
    while (R - L > 1) {
      ll mid = (L + R) / 2;
      if (check(k, mid)) L = mid;
      else R = mid;
    }

    cout << L << "\n "[q > 0];
  }

  return 0;
}