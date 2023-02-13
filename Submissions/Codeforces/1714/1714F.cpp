#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> construct_bamboo(int x, int y, int z, int n) {
  assert(x == 0);
  vector<pair<int, int>> ans;
  int curr = 1, nxt = 4;
  while (y > 1) ans.push_back({curr, nxt}), curr = nxt, nxt++, y--;
  ans.push_back({curr, 3});
  curr = 3;
  while (z > 1) ans.push_back({curr, nxt}), curr = nxt, nxt++, z--;
  ans.push_back({curr, 2});
  while (nxt <= n) ans.push_back({1, nxt}), nxt++;
  return ans;
}

vector<pair<int, int>> construct_tree(int x, int y, int z, int n) {
  vector<pair<int, int>> ans;
  int curr = 1, nxt = 4;
  while (y) ans.push_back({curr, nxt}), curr = nxt, nxt++, y--;
  int cross = curr;
  while (x > 1) ans.push_back({curr, nxt}), curr = nxt, nxt++, x--;
  ans.push_back({curr, 3});
  curr = cross;
  while (z > 1) ans.push_back({curr, nxt}), curr = nxt, nxt++, z--;
  ans.push_back({curr, 2});
  while (nxt <= n) ans.push_back({1, nxt}), nxt++;
  return ans;
}

void test_case() {
  int n;
  cin >> n;

  int d12, d23, d31;
  cin >> d12 >> d23 >> d31;

  int y2 = d31 + d12 - d23;
  if (y2 < 0 or y2 % 2 != 0) {
    cout << "NO\n";
    return;
  }
  int y = y2 / 2;
  int z = d12 - y;
  if (z < 0) {
    cout << "NO\n";
    return;
  }
  int x = d31 - y;
  if (x < 0) {
    cout << "NO\n";
    return;
  }

  if (1 + x + y + z > n) {
    cout << "NO\n";
    return;
  }

  cout << "YES\n";
  vector<pair<int, int>> ans;
  if (x == 0) {
    ans = construct_bamboo(x, y, z, n);
  }
  else if (y == 0) {
    ans = construct_bamboo(y, x, z, n);
    for (auto & [u, v] : ans) {
      if (u == 1) u = 3;
      else if (u == 3) u = 1;
      if (v == 1) v = 3;
      else if (v == 3) v = 1;
    }
  }
  else if (z == 0) {
    ans = construct_bamboo(z, y, x, n);
    for (auto & [u, v] : ans) {
      if (u == 2) u = 3;
      else if (u == 3) u = 2;
      if (v == 2) v = 3;
      else if (v == 3) v = 2;
    }
  }
  else {
    ans = construct_tree(x, y, z, n);
  }

  for (auto [u, v] : ans) cout << u << " " << v << "\n";
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