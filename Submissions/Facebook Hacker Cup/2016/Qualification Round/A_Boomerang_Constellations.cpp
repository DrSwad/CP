#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n;
  cin >> n;

  vector<int> x(n), y(n);
  for (int i = 0; i < n; i++) {
    cin >> x[i] >> y[i];
  }

  ll ans = 0;

  for (int i = 0; i < n; i++) {
    vector<ll> dists;

    for (int j = 0; j < n; j++) {
      if (i != j) {
        ll dx = x[i] - x[j];
        ll dy = y[i] - y[j];
        dists.push_back(dx * dx + dy * dy);
      }
    }

    sort(dists.begin(), dists.end());

    for (int l = 0; l < dists.size(); ) {
      int r = l;
      while (r < dists.size() and dists[r] == dists[l]) r++;

      int tot = r - l;
      ans += tot * (tot - 1) / 2;

      l = r;
    }
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}