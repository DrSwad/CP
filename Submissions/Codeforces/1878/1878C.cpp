#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll sum(ll n) {
  return n * (n + 1) / 2;
}

ll sum(ll l, ll r) {
  return sum(r) - sum(l - 1);
}

void test_case() {
  ll n, k, x;
  cin >> n >> k >> x;

  if (sum(1ll, k) <= x and x <= sum(n - k + 1, n)) cout << "YES\n";
  else cout << "NO\n";
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