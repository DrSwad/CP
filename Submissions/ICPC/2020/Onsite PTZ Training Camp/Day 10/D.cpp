#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<ll> convert_base(ll n, ll k) {
  vector<ll> d;
  while (n) {
    d.push_back(n % k);
    n /= k;
  }
  return d;
}

ll base10_value(vector<ll> num, ll base) {
  int nd = num.size();
  ll value = 0;
  for (ll d : num) {
    value = value * base + d;
  }
  return value;
}

tuple<ll, vector<ll>, vector<ll>> solve(ll k, vector<ll> dl, vector<ll> dr) {
  int nd = dl.size();
  assert(dr.size() == nd);

  int st;
  for (st = 0; st < nd; st++) {
    if (dl[st] != dr[st]) break;
  }

  {
    bool flag = true;
    for (int i = st + 1; i < nd; i++) {
      if (dr[i] != k - 1) {
        flag = false;
        break;
      }
    }
    if (flag) {
      ll m = nd;
      for (ll d : dr) m += d;
      return {m, dr, dr};
    }
  }

  vector<ll> min_n;
  for (int i = 0; i <= st; i++) min_n.push_back(dl[i]);
  for (int i = st + 1; i < nd; i++) min_n.push_back(k - 1);
  ll m = nd;
  for (ll d : min_n) m += d;

  int st2;
  for (st2 = st + 1; st2 < nd; st2++) {
    if (dr[st2] < k - 1) break;
  }
  assert(st2 < nd);

  vector<ll> max_n(nd, k - 1);
  for (int i = 0; i <= st; i++) {
    max_n[i] = dr[i];
  }

  debug(k, dl, dr);

  {
    max_n[st2] = k - 2;
    ll rr = base10_value(dr, k);
    ll nr = base10_value(max_n, k);
    if (nr <= rr) {
      if (dl[0] > 0) {
        return {m, min_n, max_n};
      }
      else {
        min_n = max_n;
        min_n[st2] = dr[st2];
        min_n[st + 1] = k - 2;
        return {m, min_n, max_n};
      }
    }
    max_n[st2] = dr[st2];
  }

  cerr << "Here\n";
  if (st2 > st + 1) {
    max_n[st2 - 1] = k - 2;
    ll rr = base10_value(dr, k);
    ll nr = base10_value(max_n, k);
    if (nr <= rr) {
      if (dl[0] > 0) {
        return {m, min_n, max_n};
      }
      else {
        min_n = max_n;
        min_n[st2 - 1] = dr[st2];
        min_n[st + 1] = k - 2;
        return {m, min_n, max_n};
      }
    }
    max_n[st2 - 1] = dr[st2 - 1];
  }

  return {m, min_n, min_n};
}

void test_case() {
  ll k, l, r;
  cin >> k >> l >> r;

  vector<ll> dl = convert_base(l, k);
  vector<ll> dr = convert_base(r, k);
  assert(dr.size() >= dl.size());
  reverse(dl.begin(), dl.end());
  reverse(dr.begin(), dr.end());
  if (dl.size() < dr.size()) {
    dl.clear();
    dl.push_back(dr[0] - 1);
    for (int i = 1; i < dr.size(); i++) {
      dl.push_back(k - 1);
    }
  }

  auto [m, d_min_n, d_max_n] = solve(k, dl, dr);
  ll min_n = base10_value(d_min_n, k);
  ll max_n = base10_value(d_max_n, k);
  cout << m - 2 << " " << min_n << " " << max_n << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}