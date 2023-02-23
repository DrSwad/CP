#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int h, w, n;
  cin >> h >> w >> n;

  map<pair<int, int>, int> mp;

  while (n--) {
    int x, y;
    cin >> x >> y;

    for (int nx = x - 2; nx <= x; nx++) {
      for (int ny = y - 2; ny <= y; ny++) {
        if (1 <= nx and nx + 2 <= h and 1 <= ny and ny + 2 <= w) {
          mp[{nx, ny}]++;
        }
      }
    }
  }

  vector<long long> ans(10);
  for (auto [cell, freq] : mp) {
    ans[freq]++;
  }

  ans[0] = (h - 2) * 1ll * (w - 2);
  for (int i = 1; i < 10; i++) {
    ans[0] -= ans[i];
  }

  for (int i = 0; i < 10; i++) {
    cout << ans[i] << "\n";
  }

  return 0;
}