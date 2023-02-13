#include <bits/stdc++.h>
using namespace std;

const int W = 4000 + 5;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  vector<vector<int>> bells(W);
  for (int i = 0; i < n; i++) {
    int m, c;
    cin >> m >> c;
    bells[m].push_back(c);
  }

  for (auto &vv : bells) {
    sort(vv.begin(), vv.end(), greater<int>());
    for (int i = 0; i < vv.size(); i++) {
      if (i > 0) vv[i] += vv[i - 1];
    }
  }

  int ans_x = 0, ans_sum = 0;
  for (int x = 1; x < W; x++) {
    vector<int> v;
    for (auto &vv : bells) {
      if (vv.size() >= x) {
        v.push_back(vv[x - 1]);
      }
    }
    if (v.size() >= k) {
      ans_x = x;
      sort(v.begin(), v.end(), greater<int>());
      ans_sum = accumulate(v.begin(), v.begin() + k, 0);
    }
  }

  cout << ans_x << " " << ans_sum << endl;

  return 0;
}