#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<ll> x(n);
  for (ll &i : x) cin >> i;

  vector<ll> d(n);
  for (ll &i : d) cin >> i;

  vector<ll> coords;
  for (ll i : x) {
    for (ll j : d) {
      coords.push_back(i - j);
      coords.push_back(i + j + 1);
    }
  }

  sort(coords.begin(), coords.end());

  ll ans = 0;
  for (int i = 0; i < coords.size(); i++) {
    int r = lower_bound(x.begin(), x.end(), coords[i]) - x.begin();
    int l = r - 1;

    bool okay = true;

    for (int j = 0; j < n; j++) {
      if (l != -1 and abs(x[l] - coords[i]) <= d[j]) {
        l--;
        continue;
      }
      if (r != n and abs(x[r] - coords[i]) <= d[j]) {
        r++;
        continue;
      }
      okay = false;
    }

    if (okay) {
      assert(i + 1 < coords.size());
      ans += coords[i + 1] - coords[i];
    }
  }

  cout << ans << "\n";

  return 0;
}