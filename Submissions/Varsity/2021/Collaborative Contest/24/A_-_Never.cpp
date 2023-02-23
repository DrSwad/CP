#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e5 + 5;
const int D = 50;

int n;
ll a[N];
ll ans;
ll basis[D];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  ll bit_freq = 0;
  for (int i = 0; i < n; i++) {
    bit_freq ^= a[i];
  }
  ll active_mask = 0;
  for (int i = D - 1; i >= 0; i--) {
    if (bit_freq >> i & 1) {
      ans += 1ll << i;
    }
    else {
      active_mask |= 1ll << i;
    }
  }

  for (int i = 0; i < n; i++) {
    a[i] &= active_mask;
  }

  for (int i = 0; i < n; i++) {
    for (int d = D - 1; d >= 0; d--) {
      if (a[i] >> d & 1) {
        if (basis[d]) {
          a[i] ^= basis[d];
        }
        else {
          basis[d] = a[i];
          break;
        }
      }
    }
  }

  ll need = (1ll << D) - 1;
  for (int d = D - 1; d >= 0; d--) {
    if (need >> d & 1) {
      if (basis[d]) {
        ans += 1ll << (d + 1);
        need ^= basis[d];
      }
    }
    else {
      ans += 1ll << (d + 1);
    }
  }

  cout << ans << "\n";

  return 0;
}