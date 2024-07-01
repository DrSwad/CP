#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n, k;
  cin >> n >> k;

  vector<int> f(n);
  vector<ll> p(n);
  {
    vector<pair<ll, int>> v(n);
    for (int i = 0; i < n; i++) cin >> v[i].second;
    for (int i = 0; i < n; i++) cin >> v[i].first;
    for (int i = 0; i < n; i++) {
      v[i].first *= v[i].second;
    }
    sort(v.begin(), v.end());
    for (int i = 0; i < n; i++) {
      p[i] = v[i].first;
      f[i] = v[i].second;
    }
  }

  int ans = n;

  function<void(ll, int, set<ll>&)> consider =
    [&](ll p, int f, set<ll> &st) {
      if (f > k + 1) {
        ll l = (p - k + f - 1) / f * f;
        ll r = l + f - k;
        if (l > p) r = l - k, l = p - k - 1;
        st.erase(st.upper_bound(l), st.lower_bound(r));
      }
    };

  for (int l = 0; l < n; l++) {
    set<ll> st;
    for (ll x = max(1ll, p[l] - k); x <= p[l]; x++) {
      st.insert(st.end(), x);
    }
    for (int i = 0; i < l and !st.empty(); i++) {
      consider(p[l], f[i], st);
    }
    int r;
    for (r = n; r > l and (st.empty() or p[r - 1] - *st.rbegin() > k); r--) {
      consider(p[l], f[r - 1], st);
    }

    ans = min(ans, n - (r - l));
  }

  cout << ans << "\n";
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