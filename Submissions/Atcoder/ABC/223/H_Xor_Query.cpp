#include <bits/stdc++.h>
using namespace std;

const int D = 60;
typedef long long ll;

pair<ll, int> insert(const vector<ll> &basis, ll v) {
  for (int i = 0; i < D and v; i++) {
    if (!(v >> i & 1)) continue;
    if (!basis[i]) { return {v, i}; }
    v ^= basis[i];
  }
  return {0, D};
}

vector<bool> query(const vector<ll> &basis, ll v) {
  vector<bool> used(D, false);
  for (int i = 0; i < D and v; i++) {
    if (!(v >> i & 1)) continue;
    if (!basis[i]) {
      fill(used.begin(), used.end(), false);
      break;
    }
    v ^= basis[i];
    used[i] = true;
  }
  return used;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, q;
  cin >> n >> q;

  vector<ll> a(n);
  for (ll &i : a) cin >> i;

  vector<vector<pair<ll, int>>> dp(n + 1, vector<pair<ll, int>>(D, make_pair(0, n)));

  for (int i = n - 1; i >= 0; i--) {
    vector<ll> basis(D, 0);

    auto try_insert = [&](int id) {
      if (id >= n) return;
      auto [nv, at] = insert(basis, a[id]);
      if (at < D) {
        basis[at] = nv;
        dp[i][at] = {nv, id};
      }
    };

    try_insert(i);
    for (int j = 0; j < D; j++) {
      try_insert(dp[i + 1][j].second);
    }
  }

  while (q--) {
    int l, r;
    ll x;
    cin >> l >> r >> x;
    l--, r--;

    if (x == 0) {
      cout << "Yes\n";
      continue;
    }

    vector<ll> basis(D);
    for (int j = 0; j < D; j++) {
      basis[j] = dp[l][j].first;
    }
    vector<bool> used = query(basis, x);

    if (!any_of(used.begin(), used.end(), [&](bool i) {return i;})) {
      cout << "No\n";
      continue;
    }

    bool possible = true;
    for (int j = 0; j < D; j++) {
      if (used[j] and dp[l][j].second > r) {
        possible = false;
        break;
      }
    }

    cout << (possible ? "Yes\n" : "No\n");
  }

  return 0;
}