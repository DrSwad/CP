#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e5 + 5;

int n;
ll W;
ll w[N], cost[N];

void test_case() {
  scanf("%d %lld", &n, &W);
  for (int i = 1; i <= n; i++) {
    scanf("%lld %lld", &w[i], &cost[i]);
  }

  vector<int> order(n);
  iota(order.begin(), order.end(), 1);
  sort(order.begin(), order.end(), [&](int i, int j) {
    return cost[i] * w[j] > cost[j] * w[i];
  });

  vector<int> small_half, big_half;
  for (int id : order) {
    if (w[id] > W / 2) big_half.push_back(id);
    else small_half.push_back(id);
  }
  big_half.push_back(0);

  vector<ll> small_w_pref, small_cost_pref;
  small_w_pref.push_back(0);
  small_cost_pref.push_back(0);
  for (int id : small_half) {
    small_w_pref.push_back(small_w_pref.back() + w[id]);
    small_cost_pref.push_back(small_cost_pref.back() + cost[id]);
  }

  int best_big = -1;
  ll best_cost = -1;
  ll WW = W * 3 / 2;

  for (int big_id : big_half) {
    if (w[big_id] > WW) continue;
    ll rem_w = WW - w[big_id];

    int at = upper_bound(small_w_pref.begin(), small_w_pref.end(), rem_w) - small_w_pref.begin() - 1;
    ll curr_cost = cost[big_id] + small_cost_pref[at];

    if (curr_cost > best_cost) {
      best_cost = curr_cost;
      best_big = big_id;
    }
  }

  assert(best_big != -1);

  vector<int> ans;
  ll rem_w = WW - w[best_big];
  if (best_big) {
    ans.push_back(best_big);
  }

  int at = upper_bound(small_w_pref.begin(), small_w_pref.end(), rem_w) - small_w_pref.begin() - 1;
  for (int i = 1; i <= at; i++) {
    ans.push_back(small_half[i - 1]);
  }

  printf("%d\n", (int)ans.size());
  for (int i = 0; i < ans.size(); i++) {
    if (i) printf(" ");
    printf("%d", ans[i]);
  }
  puts("");
}

int main() {
  int t;
  cin >> t;

  while (t--) {
    test_case();
  }

  return 0;
}