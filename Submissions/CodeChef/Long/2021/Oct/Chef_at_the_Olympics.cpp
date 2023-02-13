#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e5 + 5;

int n, q;
ll g1, s1, b1;
tuple<ll, ll, ll> v[N];
ll vg[N];
ll vgs[N], vgf[N];

int solve1(ll k) {
  if (k <= s1 + b1) {
    ll rem = k;
    ll ng = g1, ns = s1, nb = b1;
    if (rem) {
      ll take = min(rem, nb);
      rem -= take;
      nb -= take;
      ng += take;
    }
    if (rem) {
      ll take = min(rem, ns);
      rem -= take;
      ns -= take;
      ng += take;
    }

    return (n + 1) - (upper_bound(v, v + n, make_tuple(ng, ns, nb)) - v);
  }
  else {
    ll ng = g1 + s1 + b1;
    k -= s1 + b1;

    int up = upper_bound(v, v + n, make_tuple(ng, 0, 0)) - v;
    int L = up, R = n;
    if (ng > 0) {
      while (L != R) {
        int mid = (L + R + 1) / 2;
        ll need = (vg[mid] - vg[up]) - (ll)(ng - 1) * (mid - up);
        if (need <= k) L = mid;
        else R = mid - 1;
      }
    }

    return (n + 1) - L;
  }
}

int solve2(ll k) {
  ll take = b1 + (s1 - 1);
  ll ng = g1 + take;
  k -= take;

  int up = upper_bound(v, v + n, make_tuple(ng, 1, 0)) - v;
  int L = up, R = n;
  while (L != R) {
    int mid = (L + R + 1) / 2;
    ll need = (vgs[mid] - vgs[up]) - (ll)ng * (vgf[mid] - vgf[up]);
    if (need <= k) L = mid;
    else R = mid - 1;
  }

  return (n + 1) - (up + (vgf[L] - vgf[up]));
}

int solve3(ll k) {
  ll take = min(k, b1 + (s1 - 2));
  ll ng = g1 + take;
  ll ns = s1 - (take - b1);
  ll nb = 0;

  int up = upper_bound(v, v + n, make_tuple(ng, ns, nb)) - v;
  if (up != 0) {
    if (up == n) return 1;
    int mx = up - 1;

    take = max(b1, get<0>(v[mx]) - g1);
    ll ng = g1 + take;
    ll ns = s1 - (take - b1);
    ll nb = 0;
    if (v[mx] > make_tuple(ng, ns, nb)) take++;
  }
  else {
    take = b1;
  }

  k -= take;
  ng = g1 + take;
  ns = s1 - (take - b1);
  nb = 0;

  auto vv = v[up];
  get<0>(vv) -= k;
  get<2>(vv) += k;
  assert(k == 0 or vv != v[up]);

  int worse = up + (vv <= make_tuple(ng, ns, nb) ? 1 : 0);
  return (n + 1) - worse;
}

int brute() {
  g1 += s1 + b1;
  s1 = b1 = 0;
  for (int i = 0; i < n; i++) {
    auto & [g, s, b] = v[i];
    b += g + s;
    g = s = 0;
  }

  return (n + 1) - (upper_bound(v, v + n, make_tuple(g1, s1, b1)) - v);
}

void test_case() {
  cin >> n >> q;
  n--;

  cin >> g1 >> s1 >> b1;

  for (int i = 0; i < n; i++) {
    auto & [g, s, b] = v[i];
    cin >> g >> s >> b;
  }

  sort(v, v + n);

  vg[0] = vgs[0] = vgf[0] = 0;
  for (int i = 1; i <= n; i++) {
    auto [g, s, b] = v[i - 1];
    vg[i] = vg[i - 1] + g;
    vgs[i] = vgs[i - 1] + (s == 0 ? g : 0);
    vgf[i] = vgf[i - 1] + (s == 0 ? 1 : 0);
  }

  ll mxk = s1 + b1;
  for (int i = 0; i < n; i++) {
    auto & [g, s, b] = v[i];
    mxk += g + s;
  }

  while (q--) {
    ll k;
    cin >> k;

    if (k >= mxk) {
      cout << brute() << "\n";
      continue;
    }

    if (n == 0) {
      cout << "1\n";
      continue;
    }

    int ans1 = solve1(k);
    int ans2 = n + 1, ans3 = n + 1;
    if (s1 >= 1 and k > b1 + (s1 - 1)) ans2 = solve2(k);
    if (s1 >= 2 and k > b1) ans3 = solve3(k);
    assert(ans3 >= ans1 - 1);

    cout << min(ans1, min(ans2, ans3)) << "\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}