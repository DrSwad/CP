#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n, k;
  cin >> n >> k;

  vector<ll> a(n);
  for (ll &i : a) cin >> i;

  vector<pair<int, int>> op(k);
  for (auto & [x, y] : op) cin >> x >> y;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}