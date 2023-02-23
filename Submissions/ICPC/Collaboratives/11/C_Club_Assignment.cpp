#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e5 + 5;

int n;
ll w[N];
int ansv[N];

ll assignGroup(vector<int> v) {
  int sz = v.size();

  int best_mask;
  ll best_val = 0;

  for (int mask = 0; mask < 1 << sz; mask++) {
    ll val = LLONG_MAX;
    for (int i = 0; i < sz; i++) {
      for (int j = i + 1; j < sz; j++) {
        if ((mask >> i & 1) == (mask >> j & 1)) {
          val = min(val, w[v[i]] ^ w[v[j]]);
        }
      }
    }
    if (val >= best_val) {
      best_val = val;
      best_mask = mask;
    }
  }

  for (int i = 0; i < sz; i++) {
    ansv[v[i]] = (best_mask >> i & 1) + 1;
  }

  return best_val;
}

// 0 <= bit <= 30
vector<vector<int>> bitGroup(int bit) {
  ll full_mask = (1ll << 31) - 1;
  ll mask = full_mask - ((1ll << bit) - 1);

  vector<int> order(n);
  iota(order.begin(), order.end(), 0);
  sort(order.begin(), order.end(), [&](int i, int j) {
    return (w[i] & mask) < (w[j] & mask);
  });

  vector<vector<int>> ret;
  for (int i : order) {
    ll cur = w[i] & mask;
    if (ret.empty()) ret.push_back({i});
    else {
      ll prv = w[ret.back().back()] & mask;
      if (cur == prv) ret.back().push_back(i);
      else ret.push_back({i});
    }
  }

  return ret;
}

void solve() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) scanf("%lld", &w[i]);

  int bit = 30;
  do {
    auto groups = bitGroup(bit);
    int max_sz = 0;
    for (auto&grp : groups) max_sz = max(max_sz, (int)grp.size());

    if (max_sz <= 2) break;

    bit--;
  } while (bit >= 0);

  if (bit == -1) {
    puts("0");
    for (int i = 0; i < n; i++) printf("%d", (i & 1) + 1);
    puts("");
    return;
  }

  bit++;
  assert(bit <= 30);

  auto groups = bitGroup(bit);

  ll ans = LLONG_MAX;
  for (auto&grp : groups) ans = min(ans, assignGroup(grp));

  printf("%lld\n", ans);
  for (int i = 0; i < n; i++) printf("%d", ansv[i]);
  puts("");
}

int main() {
  int t;
  cin >> t;

  while (t--) solve();

  return 0;
}