#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, k;
  cin >> n >> k;

  vector<bool> vis(n, 0);
  for (int i = 0; i < n; i++) {
    int p;
    cin >> p;
    if (i < k) vis[p - 1] = true;
  }

  cout << k - accumulate(vis.begin(), vis.begin() + k, 0) << "\n";
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