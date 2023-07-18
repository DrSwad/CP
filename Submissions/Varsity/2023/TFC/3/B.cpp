#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int B = 62;

void test_case() {
  int n;
  cin >> n;

  vector<ll> a(n);
  for (ll &i : a) cin >> i;

  if (n % 2 == 0) cout << "0\n";
  else {
    ll mn = LLONG_MAX;
    for (int i = 0; i < n; i++) {
      int mx_b = 64 - __builtin_clzll(a[i]);
      for (int b = 0; b < mx_b; b++) {
        if ((a[i] >> b & 1) == 0) {
          mn = min(mn, 1ll << b);
          break;
        }
      }
    }
    cout << (mn == LLONG_MAX ? -1 : mn) << "\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}