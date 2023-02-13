#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int x, y, z, k;
  cin >> x >> y >> z >> k;

  vector<ll> a(x), b(y), c(z);
  for (auto &i : a) cin >> i;
  for (auto &i : b) cin >> i;
  for (auto &i : c) cin >> i;

  vector<ll> d;
  for (ll i : a) for (ll j : b) d.push_back(i + j);
  sort(d.begin(), d.end(), greater<ll>());
  if (d.size() > k) d.resize(k);

  vector<ll> e;
  for (ll i : c) for (ll j : d) e.push_back(i + j);
  sort(e.begin(), e.end(), greater<ll>());
  if (e.size() > k) e.resize(k);

  for (ll i : e) cout << i << "\n";

  return 0;
}