#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<int> d[2];
  for (int i = 0; i < n; i++) {
    d[a[i] > 1].push_back(i);
  }

  sort(d[1].begin(), d[1].end(), [&](int i, int j) {
    return a[i] < a[j];
  });
  if (d[1].size() > 1) swap(d[1][0], d[1][d[1].size() - 2]);

  vector<pair<int, int>> e;
  int ans = (int)d[1].size() - 1;

  if (d[1].size() > 1) {
    for (int i = 0; i < d[1].size(); i++) {
      a[d[1][i]]--;
      if (i > 0 and i < d[1].size() - 1) a[d[1][i]]--;
      if (i < d[1].size() - 1) {
        e.push_back({d[1][i], d[1][i + 1]});
      }
    }
  }

  if (d[1].size()) {
    if (d[0].size() and a[d[1].back()]) {
      e.push_back({d[0].back(), d[1].back()});
      a[d[0].back()]--;
      a[d[1].back()]--;
      d[0].pop_back();
      ans++;
    }
    if (d[0].size() and a[d[1][0]]) {
      e.push_back({d[0].back(), d[1][0]});
      a[d[0].back()]--;
      a[d[1][0]]--;
      d[0].pop_back();
      ans++;
    }
    while (d[0].size()) {
      int with;
      for (with = 0; with < d[1].size(); with++) {
        if (a[d[1][with]]) break;
      }
      if (with == d[1].size()) break;
      e.push_back({d[0].back(), d[1][with]});
      a[d[0].back()]--;
      a[d[1][with]]--;
      d[0].pop_back();
    }
  }

  for (int i : d[0]) {
    if (a[i]) {
      cout << "NO\n";
      return;
    }
  }

  cout << "YES " << ans << "\n" << e.size() << "\n";
  for (auto [u, v] : e) {
    cout << u + 1 << " " << v + 1 << "\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  // cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}