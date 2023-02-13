#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
const ll MAX_T = 1e8;
const ld eps = 1e-10;
const int g = 10;

/*
   h = u * t - 0.5 * g * t * t
     = u * (x - st) - 0.5 * g * (x - st) * (x - st)
     = u * x - u * st - 5 * (x * x - 2 * x * st + st * st)
     = -(u * st + 5 * st * st) + x * (u + 10 * st) - 5 * x^2
 */
tuple<ll, ll, ll> height_equation(ll u, ll st) {
  return {-(u * st + 5 * st * st), u + 10 * st, -5};
}

bool check(ll b, ll c, ll x) {
  return c + b * x > 0;
}

ll smaller_int(ld val) {
  return val - eps;
}

ll larger_or_equal_int(ld val) {
  return (ll)(val - eps) + 1;
}

pair<ll, ll> get_range(ll st1, ll u1, ll st2, ll u2, ll tl, ll tr) {
  if (tr < tl) return {-1, -1};

  auto [c1, b1, a1] = height_equation(u1, st1);
  auto [c2, b2, a2] = height_equation(u2, st2);
  ll a = a2 - a1;
  ll b = b2 - b1;
  ll c = c2 - c1;
  assert(a == 0);

  if (b == 0) {
    if (c > 0) return {tl, tr};
    else return {-1, -1};
  }

  ll tm = (-c / (ld)b) - 10;
  while (check(b, c, tm) == check(b, c, tm + 1)) tm++;

  if (check(b, c, tm)) {
    if (tm >= tl) return {tl, min(tr, tm)};
    else return {-1, -1};
  }
  else {
    tm = tm + 1;
    if (tm <= tr) return {max(tl, tm), tr};
    else return {-1, -1};
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;

  vector<int> st(n), u(n);
  for (int i = 0; i < n; i++) {
    cin >> st[i] >> u[i];
  }

  vector<int> qt(q);
  for (int &t : qt) cin >> t;

  vector<pair<ll, ll>> ranges;
  for (int i = 1; i < n; i++) {
    ll s0 = st[0], si = st[i];
    ll f0 = larger_or_equal_int(st[0] + (ld)2 * u[0] / g);
    ll fi = larger_or_equal_int(st[i] + (ld)2 * u[i] / g);
    assert(f0 > s0 and fi > si);
    if (fi == si + 1) continue;

    if (si < s0) {
      ranges.emplace_back(si + 1, min(s0, fi - 1));
    }

    if (fi > f0) {
      ranges.emplace_back(max(f0, si + 1), fi - 1);
    }

    ll tl = max(s0 + 1, si + 1);
    ll tr = min(f0 - 1, fi - 1);
    if (tl <= tr) {
      pair<ll, ll> range = get_range(st[0], u[0], st[i], u[i], tl, min(smaller_int(f0), smaller_int(fi)));
      ranges.push_back(range);
    }
  }

  vector<ll> vl, vr;
  for (auto [l, r] : ranges) {
    vl.push_back(l);
    vr.push_back(r);
  }
  sort(vl.begin(), vl.end());
  sort(vr.begin(), vr.end());

  for (int i = 0; i < q; i++) {
    int ans = ranges.size();
    ans -= lower_bound(vr.begin(), vr.end(), qt[i]) - vr.begin();
    ans -= vl.end() - upper_bound(vl.begin(), vl.end(), qt[i]);
    cout << ans << "\n";
  }

  return 0;
}