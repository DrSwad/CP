#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<int> c(n);
  for (int &i : c) cin >> i, i--;

  vector<int> x(m);
  for (int &i : x) cin >> i;

  if (m == 1) {
    cout << x[0] << "\n";
    return 0;
  }

  vector<ll> banned_mask(m, 0);
  for (int i = 0; i < n - 1; i++) {
    int c0 = c[i], c1 = c[i + 1];
    banned_mask[c0] |= 1ll << c1;
    banned_mask[c1] |= 1ll << c0;
  }

  int low_half = m / 2, high_half = m - low_half;

  vector<int> low_half_save(1 << low_half);
  low_half_save[0] = 0;
  for (int low_mask = 1; low_mask < 1 << low_half; low_mask++) {
    low_half_save[low_mask] = 0;
    if ((low_mask & 1ll << c[0]) == 0 and (low_mask & 1ll << c[n - 1]) == 0) {
      for (int i = 0; i < low_half; i++) {
        if (low_mask >> i & 1) {
          if (banned_mask[i] & low_mask) {
            low_half_save[low_mask] = 0;
            break;
          }
          low_half_save[low_mask] += x[i];
        }
      }
    }

    for (int i = 0; i < low_half; i++){
      if (low_mask >> i & 1) {
        low_half_save[low_mask] = max(low_half_save[low_mask], low_half_save[low_mask ^ 1 << i]);
      }
    }
  }

  int max_save = 0;

  for (ll high_mask = 0; high_mask < 1ll << m; high_mask += 1ll << low_half) {
    if ((high_mask & 1ll << c[0]) or (high_mask & 1ll << c[n - 1])) continue;

    ll allowed_mask = (1ll << m) - 1;
    for (int i = low_half; i < m; i++) {
      if (high_mask >> i & 1) {
        allowed_mask &= (~banned_mask[i]);
      }
    }

    if ((allowed_mask & high_mask) != high_mask) continue;

    int low_mask = allowed_mask & ((1ll << low_half) - 1);
    int cur_save = low_half_save[low_mask];
    for (int i = low_half; i < m; i++) {
      if (high_mask >> i & 1) {
        cur_save += x[i];
      }
    }

    max_save = max(max_save, cur_save);
  }

  int ans = accumulate(x.begin(), x.end(), 0) - max_save;
  cout << ans << "\n";

  return 0;
}
