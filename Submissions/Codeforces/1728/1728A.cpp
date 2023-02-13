#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  map<int, int> mp;
  for (int i = 1; i <= n; i++) {
    int cnt;
    cin >> cnt;
    mp[i] = cnt;
  }

  while (mp.size() > 1) {
    mp.begin()->second--;
    next(mp.begin())->second--;
    if (next(mp.begin())->second == 0) mp.erase(next(mp.begin())->first);
    if (mp.begin()->second == 0) mp.erase(mp.begin()->first);
  }

  cout << mp.begin()->first << "\n";
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