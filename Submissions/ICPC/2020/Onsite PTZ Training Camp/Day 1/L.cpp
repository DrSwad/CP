#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n, m;
  ll k;
  cin >> n >> m >> k;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  sort(a.begin(), a.end());

  {
    int at;
    for (at = n - 1; at > 0; at--) {
      int diff = a[at] - a[at - 1];
      ll need = 1ll * diff * (n - at);
      if (k < need) break;
      k -= need;
    }

    for (int i = n - 1; i >= at; i--) {
      a[i] = a[at];
    }

    ll times = min((ll)a[at], k / (n - at));
    for (int i = n - 1; i >= at; i--) {
      a[i] -= times;
      k -= times;
    }

    for (int i = at; i < n; i++) {
      if (a[i] and k) a[i]--, k--;
    }
  }

  assert(is_sorted(a.begin(), a.end()));

  ll ans = 0ll;
  for (int i : a) {
    ans += 1ll * i * (i + 1) / 2;
  }

  for (int at = n - 1; at >= 0 and m; at--) {
    while (a[at] and m) {
      ans -= a[at];
      a[at]--;
      m--;
    }
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  // cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}