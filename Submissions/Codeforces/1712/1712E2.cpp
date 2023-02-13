#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 2e5 + 5;
const int BLOCK = 500;

vector<vector<int>> divs(N + 1);
vector<vector<int>> mul_pref_sum(N + 1);

void init() {
  for (int d = 1; d < N; d++) {
    for (int m = d + d; m < N; m += d) {
      divs[m].push_back(d);
    }
  }

  for (int d = 1; d < N; d++) {
    for (int m = d + d; m < N; m += d) {
      int div_cnt = divs[m].end() - upper_bound(divs[m].begin(), divs[m].end(), d);
      ll prv = mul_pref_sum[d].empty() ? 0 : mul_pref_sum[d].back();
      mul_pref_sum[d].push_back(prv + div_cnt);
    }
  }
}

constexpr int logn = 20;
constexpr int maxn = 1 << logn;
ll hilbertOrder(int x, int y) {
  ll d = 0;
  for (int s = 1 << (logn - 1); s; s >>= 1) {
    bool rx = x & s, ry = y & s;
    d = d << 2 | rx * 3 ^ static_cast<int>(ry);
    if (!ry) {
      if (rx) {
        x = maxn - x;
        y = maxn - y;
      }
      swap(x, y);
    }
  }
  return d;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  init();

  int q;
  cin >> q;

  vector<pair<int, int>> queries(q);
  for (auto & [l, r] : queries) cin >> l >> r;

  vector<ll> hilbert_order(q);
  for (int i = 0; i < q; i++) {
    hilbert_order[i] = hilbertOrder(queries[i].first, queries[i].second);
  }

  vector<int> order(q);
  iota(order.begin(), order.end(), 0);
  sort(
    order.begin(),
    order.end(),
    [&](int i, int j) { return hilbert_order[i] < hilbert_order[j]; }
    );

  function<ll(int, int)> right_contrib = [&](int l, int r) {
    ll ret = 0;
    ret += 1ll * (r - l) * (r - l - 1) / 2; // add all

    int div_cnt = divs[r].end() - lower_bound(divs[r].begin(), divs[r].end(), l);
    ret -= 1ll * div_cnt * (div_cnt - 1) / 2; // remove lcm = r

    // lcm = 2r, bad case 1
    if (2 * r % 3 == 0 and 2 * r % 4 == 0) {
      int i = 2 * r / 4;
      int j = 2 * r / 3;
      if (l <= i and (r % i != 0 or r % j != 0)) ret--;
    }

    // lcm = 2r, bad case 2
    if (2 * r % 3 == 0 and 2 * r % 5 == 0) {
      int i = 2 * r / 5;
      int j = 2 * r / 3;
      if (l <= i and (r % i != 0 or r % j != 0)) ret--;
    }

    return ret;
  };

  function<ll(int, int)> left_contrib = [&](int l, int r) {
    ll ret = 0;
    ret += 1ll * (r - l) * (r - l - 1) / 2; // add all

    int mul_cnt = r / l - 1;
    if (mul_cnt) ret -= mul_pref_sum[l][mul_cnt - 1]; // remove lcm = k

    // lcm = 2k, bad case 1
    {
      int i = l;
      int k = 4 * i / 2;
      if (k <= r and 2 * k % 3 == 0) {
        int j = 2 * k / 3;
        if (l <= i and (k % i != 0 or k % j != 0)) ret--;
      }
    }

    // lcm = 2k, bad case 2
    {
      int i = l;
      if (5 * i % 2 == 0) {
        int k = 5 * i / 2;
        if (k <= r and 2 * k % 3 == 0) {
          int j = 2 * k / 3;
          if (l <= i and (k % i != 0 or k % j != 0)) ret--;
        }
      }
    }

    return ret;
  };

  ll ans = 0;

  auto include_right = [&](int l, int r) {
    ans += right_contrib(l, r);
  };

  auto remove_right = [&](int l, int r) {
    ans -= right_contrib(l, r);
  };

  auto include_left = [&](int l, int r) {
    ans += left_contrib(l, r);
  };

  auto remove_left = [&](int l, int r) {
    ans -= left_contrib(l, r);
  };

  int l = 1, r = 1;
  vector<ll> query_ans(q);

  for (int qi : order) {
    auto [ql, qr] = queries[qi];
    while (l > ql) include_left(--l, r);
    while (r < qr) include_right(l, ++r);
    while (l < ql) remove_left(l++, r);
    while (r > qr) remove_right(l, r--);
    query_ans[qi] = ans;
  }

  for (ll ans : query_ans) {
    cout << ans << "\n";
  }

  return 0;
}