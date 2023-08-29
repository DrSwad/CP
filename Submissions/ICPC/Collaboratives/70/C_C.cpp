#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  ll t1, t2;
  cin >> n >> k >> t1 >> t2;

  vector<ll> m(n);
  for (ll &i : m) cin >> i;

  vector<pair<ll, ll>> interval(k);
  for (auto & [b, e] : interval) cin >> b >> e;

  map<ll, ll> bad_mp;

  for (int i = 0; i < n; i++) {
    for (auto [b, e] : interval) {
      ll bad_t1 = b - m[i];
      ll bad_t2 = e - m[i];
      bad_mp[bad_t1] = max(bad_mp[bad_t1], bad_t2);
    }
  }

  while (!bad_mp.empty() and bad_mp.begin()->first < t1) {
    auto [bad_t1, bad_t2] = *bad_mp.begin();
    bad_mp.erase(bad_mp.begin());
    if (bad_t2 >= t1) bad_mp[t1] = max(bad_mp[t1], bad_t2);
  }
  while (!bad_mp.empty() and prev(bad_mp.end())->first > t2) {
    bad_mp.erase(prev(bad_mp.end()));
  }

  for (auto & [bad_t1, bad_t2] : bad_mp) {
    bad_t2 = min(bad_t2, t2);
  }

  ll bad_sum = 0;
  ll cur_bad_t2 = 0;

  for (auto it : bad_mp) {
    ll bad_t1 = it.first;
    ll bad_t2 = it.second;
    bad_t1 = max(bad_t1, cur_bad_t2);
    cur_bad_t2 = max(cur_bad_t2, bad_t2);
    bad_sum += cur_bad_t2 - bad_t1;
  }

  cout << fixed << setprecision(10) << (long double)1 - (long double)bad_sum / (t2 - t1) << "\n";

  return 0;
}