#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n;
  ll m, c;
  cin >> n >> m >> c;

  vector<ll> a(n);
  for (ll &i : a) cin >> i;
  sort(a.begin(), a.end());

  vector<ll> v;

  for (int i = 0; i < n; i++) {
    auto it = upper_bound(v.begin(), v.end(), a[i]);
    if (it == v.end()) v.push_back(a[i] * m + c);
    else if (a[i] * m + c < *it) *it = a[i] * m + c;
  }

  cout << v.size() << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}