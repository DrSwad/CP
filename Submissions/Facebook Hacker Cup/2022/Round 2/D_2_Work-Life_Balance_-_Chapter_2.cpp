#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

class BIT {
public:
  int n;
  vector<ll> f;
  BIT(int n) : n(n) {
    f.resize(n + 1, 0ll);
  }
  void update(int p, ll v) {
    while (p <= n) f[p] += v, p += p & -p;
  }
  ll pref(int p) {
    ll ret = 0;
    while (p) ret += f[p], p -= p & -p;
    return ret;
  }
  ll range(int l, int r) {
    return pref(r) - pref(l - 1);
  }
};

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag,
  tree_order_statistics_node_update>
  ordered_set;
// find_by_order(k) : iterator to the k'th element (0-indexed)
// order_of_key(k) : number of items strictly smaller than k
// auto cmp = [](int a, int b) { return a < b; };
// tree<int, null_type, decltype(cmp)> x(cmp);
// tree<int, null_type, function<bool(int, int)>> y(
//     [](int a, int b) { return a < b; });

void test_case() {
  int n, m;
  cin >> n >> m;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<BIT> bit(2, BIT(n));
  vector<BIT> bit_pos(2, BIT(n));
  for (int i = 0; i < n; i++) {
    bit[a[i] - 1].update(i + 1, 1);
    bit_pos[a[i] - 1].update(i + 1, i + 1);
  }

  vector<ordered_set> os(2);
  for (int i = 0; i < n; i++) {
    os[a[i] - 1].insert(i + 1);
  }

  ll ans = 0;

  while (m--) {
    int at, val;
    ll pref;
    cin >> at >> val >> pref;
    int old = a[at - 1];
    a[at - 1] = val;

    bit[old - 1].update(at, -1);
    bit[val - 1].update(at, 1);

    os[old - 1].erase(at);
    os[val - 1].insert(at);

    bit_pos[old - 1].update(at, -at);
    bit_pos[val - 1].update(at, at);

    vector<vector<int>> f(2, vector<int>(2));
    for (int i = 0; i < 2; i++) {
      f[0][i] = bit[i].pref(pref);
    }
    for (int i = 0; i < 2; i++) {
      f[1][i] = bit[i].pref(n) - f[0][i];
    }

    vector<int> sum(2, 0);
    for (int it = 0; it < 2; it++) {
      for (int i = 0; i < 2; i++) {
        sum[it] += f[it][i] * (i + 1);
      }
    }

    ll moves = 0;
    if (sum[0] < sum[1]) {
      ll take = sum[1] - sum[0];
      if (f[0][0] < take or f[1][1] < take) moves = -1;
      else {
        moves = take * take;
        int pos = f[0][0] == take ? 0 : *os[0].find_by_order(f[0][0] - take - 1);
        moves += take * pref - (bit_pos[0].pref(pref) - bit_pos[0].pref(pos)) - take * (take - 1) / 2;
        pos = *os[1].find_by_order(f[0][1] + take - 1);
        moves += (bit_pos[1].pref(pos) - bit_pos[1].pref(pref)) - take * (pref + 1) - take * (take - 1) / 2;
      }
    }
    else if (sum[0] > sum[1]) {
      ll take = sum[0] - sum[1];
      if (f[0][1] < take or f[1][0] < take) moves = -1;
      else {
        moves = take * take;
        int pos = f[0][1] == take ? 0 : *os[1].find_by_order(f[0][1] - take - 1);
        moves += take * pref - (bit_pos[1].pref(pref) - bit_pos[1].pref(pos)) - take * (take - 1) / 2;
        pos = *os[0].find_by_order(f[0][0] + take - 1);
        moves += (bit_pos[0].pref(pos) - bit_pos[0].pref(pref)) - take * (pref + 1) - take * (take - 1) / 2;
      }
    }

    ans += moves;
  }

  cout << ans << "\n";
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