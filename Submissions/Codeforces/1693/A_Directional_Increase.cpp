#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n;
  cin >> n;

  vector<ll> a(n);
  for (ll &i : a) cin >> i;

  vector<ll> b(n, 0);
  for (int i = 0; i < n; i++) {
    if (b[i] > a[i]) {
      cout << "No\n";
      return;
    }

    if (b[i] == a[i] or i == n - 1) break;

    ll diff = a[i] - b[i];
    b[i] += diff;
    b[i + 1] -= diff;
  }

  cout << (a == b ? "Yes\n" : "No\n");
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