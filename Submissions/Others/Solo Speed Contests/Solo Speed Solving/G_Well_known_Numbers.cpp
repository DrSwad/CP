#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e9;

int main() {
  ll s, k;
  cin >> s >> k;

  vector<ll> v;
  v.push_back(0);
  v.push_back(1);
  while (v.back() <= N) {
    ll x = 0;
    for (int i = 1; i <= min(k, (ll)v.size()); i++) x += v[v.size() - i];
    v.push_back(x);
  }
  v.pop_back();

  vector<int> r;
  while (s) {
    int i = upper_bound(v.begin(), v.end(), s) - v.begin() - 1;
    r.push_back(i);
    s -= v[i];
  }

  reverse(r.begin(), r.end());

  if (r.size() == 1) printf("2\n0 %lld\n", v[r[0]]);
  else {
    printf("%d\n", r.size());
    for (int i = 0; i < r.size(); i++) {
      if (i) printf(" ");
      printf("%lld", v[r[i]]);
    }
    puts("");
  }

  return 0;
}