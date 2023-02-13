#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<pair<int, int>> ans;

  for (int i = 0; i < n; i++) {
    vector<int> with;
    for (int j = i + 1; j < n; j++) {
      if (a[j] < a[i]) with.push_back(j);
    }
    sort(with.begin(), with.end(), [&](int i, int j) {
      return a[i] > a[j];
    });
    with.resize(unique(with.begin(), with.end(), [&](int i, int j) {
      return a[i] == a[j];
    }) - with.begin());

    for (int j : with) {
      ans.push_back({i + 1, j + 1});
      swap(a[i], a[j]);
    }
  }

  debug(a);

  cout << ans.size() << "\n";
  for (auto [i, j] : ans) cout << i << " " << j << "\n";

  return 0;
}