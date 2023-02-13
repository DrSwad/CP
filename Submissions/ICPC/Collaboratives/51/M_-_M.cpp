#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  int ans1 = 0, ans2 = 0;
  vector<int> mids;
  for (int i = 0; i < n; i++) {
    int sz;
    cin >> sz;

    vector<int> v(sz);
    for (int &j : v) cin >> j;

    int half = sz / 2;
    ans1 += accumulate(v.begin(), v.begin() + half, 0);
    ans2 += accumulate(v.rbegin(), v.rbegin() + half, 0);

    if (sz & 1) {
      mids.push_back(v[half]);
    }
  }

  sort(mids.begin(), mids.end(), greater<int>());

  for (int i = 0; i < mids.size(); i += 2) {
    ans1 += mids[i];
    if (i + 1 < mids.size()) ans2 += mids[i + 1];
  }

  cout << ans1 << " " << ans2 << "\n";

  return 0;
}