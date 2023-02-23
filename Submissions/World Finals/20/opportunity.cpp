#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<array<int, 3>> v(n);
  for (auto &a : v) {
    cin >> a[0] >> a[1] >> a[2];
  }

  vector<ll> mx(8, LLONG_MIN);
  for (int i = 0; i < n; i++) {
    for (int mask = 0; mask < 8; mask++) {
      ll cur = 0;
      for (int j = 0; j < 3; j++) {
        if (mask >> j & 1) {
          cur += v[i][j];
        }
      }
      mx[mask] = max(mx[mask], cur);
    }
  }

  ll best_ans = LLONG_MAX, best_i;
  for (int i = 0; i < n; i++) {
    ll cur_ans = LLONG_MIN;
    for (int mask = 0; mask < 8; mask++) {
      ll cur = 0;
      for (int j = 0; j < 3; j++) {
        if (mask >> j & 1) {
          cur += v[i][j];
        }
      }
      cur_ans = max(cur_ans, mx[mask] - cur);
    }
    if (cur_ans < best_ans) {
      best_ans = cur_ans;
      best_i = i;
    }
  }

  cout << best_ans << " " << best_i + 1 << "\n";

  return 0;
}