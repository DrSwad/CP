#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<bool> vis(10, false);
  while (n--) {
    int d;
    cin >> d;
    vis[d] = true;
  }

  int rem = count(vis.begin(), vis.end(), false);
  cout << (4 * 3 / 2) * (rem * (rem - 1) / 2) << "\n";
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