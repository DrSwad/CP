#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  ll x, y;
  int n;
  cin >> x >> y >> n;

  vector<ll> a(n);
  a[n - 1] = y;
  ll d = 1;
  for (int i = n - 2; i >= 0; i--) {
    a[i] = a[i + 1] - d;
    d++;
  }

  if (a[0] < x) cout << "-1\n";
  else {
    a[0] = x;
    for (int i = 0; i < n; i++) {
      if (i) cout << " ";
      cout << a[i];
    }
    cout << "\n";
  }
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