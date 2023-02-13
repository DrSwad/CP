#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<vector<int>> piles(3);
  piles[0] = a;

  vector<pair<int, int>> ans;

  auto mv = [&](int a, int b) {
    piles[b].push_back(piles[a].back());
    piles[a].pop_back();
    ans.push_back({a + 1, b + 1});
  };

  while (!piles[0].empty()) {
    int v = piles[0].back();
    mv(0, 1);
    int moved = 0;
    while (!piles[2].empty() and piles[2].back() < v) mv(2, 0), moved++;
    mv(1, 2);
    while (moved--) mv(0, 2);
  }

  cout << ans.size() << "\n";
  for (auto [a, b] : ans) cout << a << " " << b << "\n";

  return 0;
}