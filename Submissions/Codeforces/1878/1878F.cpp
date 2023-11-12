#include <bits/stdc++.h>
using namespace std;

map<int, int> factorize(int n) {
  map<int, int> mp;
  for (int d = 2; d <= n; d++) {
    while (n % d == 0) {
      mp[d]++;
      n /= d;
    }
  }
  return mp;
}

int divisors(const map<int, int> &mp) {
  int ret = 1;
  for (auto [p, exp] : mp) {
    ret *= (exp + 1);
  }
  return ret;
}

void test_case() {
  int n, q;
  cin >> n >> q;

  auto mp0 = factorize(n);
  auto mp = mp0;
  vector<int> vx;

  while (q--) {
    int type;
    cin >> type;

    if (type == 2) mp = mp0, vx.clear();
    else {
      int x;
      cin >> x;
      vx.push_back(x);

      auto nmp = factorize(x);
      for (auto [p, exp] : nmp) mp[p] += exp;

      int d = divisors(mp);

      d /= gcd(d, n);
      for (int x : vx) d /= gcd(d, x);

      if (d == 1) cout << "YES\n";
      else cout << "NO\n";
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}