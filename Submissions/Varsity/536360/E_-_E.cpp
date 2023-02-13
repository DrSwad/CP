#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, q;
  cin >> n >> q;

  vector<int> h(n);
  for (int &i : h) cin >> i;

  vector<vector<pair<int, int>>> queries_at(n);
  for (int i = 0; i < q; i++) {
    int l, r;
    cin >> l >> r;
    l--, r--;
    if (l > r) swap(l, r);
    queries_at[l].emplace_back(r, i);
  }

  vector<int> seen;
  vector<int> ans(q);

  for (int l = n - 1; l >= 0; l--) {
    while (!seen.empty() and h[seen.back()] <= h[l]) seen.pop_back();
    for (auto [r, qi] : queries_at[l]) {
      ans[qi] = seen.rend() - upper_bound(seen.rbegin(), seen.rend(), r);
    }
    seen.push_back(l);
  }

  for (int i = 0; i < q; i++) {
    cout << ans[i] << "\n";
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