#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> v;
set<pair<int, vector<int>>> que;
set<vector<int>> banned;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;

  v.resize(n);
  for (auto &vv : v) {
    int c;
    cin >> c;

    vv.resize(c);
    for (int &a : vv) cin >> a;
  }

  int m;
  cin >> m;

  while (m--) {
    vector<int> vv(n);
    for (int &b : vv) cin >> b, b--;
    banned.insert(vv);
  }

  vector<int> mxv;
  int mxs = 0;
  for (auto &vv : v) {
    mxv.push_back((int)vv.size() - 1);
    mxs += vv.back();
  }
  que.insert(make_pair(mxs, mxv));

  while (!que.empty()) {
    auto it = que.end();
    it--;
    auto [sum, curr] = *it;
    que.erase(it);

    if (banned.find(curr) == banned.end()) {
      for (int i = 0; i < n; i++) {
        if (i) cout << " ";
        cout << curr[i] + 1;
      }
      cout << "\n";
      return 0;
    }

    for (int i = 0; i < n; i++) {
      if (curr[i] == 0) continue;
      auto nxtv = curr; nxtv[i]--;
      auto nxts = sum - v[i][curr[i]] + v[i][nxtv[i]];
      que.insert(make_pair(nxts, nxtv));
    }
  }

  assert(69 == 420);

  return 0;
}