#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

void test_case() {
  int n;
  cin >> n;

  vector<pair<int, int>> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i].first;
    a[i].second = i;
  }

  sort(a.begin(), a.end());

  vector<int> ans(n, 0);
  for (int i = 0; i < n; i++) {
    auto [val, index] = a[i];
    int rem = MOD - 1 - val;

    int at = upper_bound(a.begin(), a.end(), make_pair(rem, n)) - a.begin();

    int j = at - 1;
    if (j >= 0 and a[j].second == index) j--;
    if (j >= 0) ans[index] = max(ans[index], (val + a[j].first) % MOD);

    j = n - 1;
    if (j >= 0 and a[j].second == index) j--;
    if (j >= 0) ans[index] = max(ans[index], (val + a[j].first) % MOD);
  }

  for (int i = 0; i < n; i++) {
    if (i) cout << " ";
    cout << ans[i];
  }
  cout << "\n";
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