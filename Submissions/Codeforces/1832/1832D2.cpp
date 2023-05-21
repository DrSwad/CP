#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = ll(2e9) + 5;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  sort(a.begin(), a.end());

  vector<int> pref(n), suff(n);
  pref[0] = a[0];
  for (int i = 1; i < n; i++) {
    pref[i] = min(pref[i - 1], a[i] - i);
  }
  suff[n - 1] = a[n - 1];
  for (int i = n - 2; i >= 0; i--) {
    suff[i] = min(suff[i + 1], a[i]);
  }

  ll total = 0;
  for (int i : a) total += i;

  auto check = [&](int k, int mn) {
    int inc_moves = min(n, k);
    if ((k - inc_moves) & 1) inc_moves--;

    if (inc_moves and pref[inc_moves - 1] + k < mn) return false;
    if (inc_moves < n and suff[inc_moves] < mn) return false;

    ll extra = total + 1ll * k * inc_moves - 1ll * inc_moves * (inc_moves - 1) / 2 - 1ll * mn * n;
    return extra >= (k - inc_moves) / 2;
  };

  while (q--) {
    int k;
    cin >> k;

    ll L = -INF, R = INF;
    while (R - L > 1) {
      int mid = (L + R) / 2;
      if (check(k, mid)) L = mid;
      else R = mid;
    }

    cout << L << "\n "[q > 0];
  }

  return 0;
}