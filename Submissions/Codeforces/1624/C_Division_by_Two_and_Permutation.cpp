#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<bool> vis(n, false);
  for (int i = 0; i < n; i++) {
    while (a[i]) {
      if (a[i] <= n and !vis[a[i] - 1]) {
        vis[a[i] - 1] = true;
        break;
      }
      else a[i] /= 2;
    }
  }

  cout << (accumulate(vis.begin(), vis.end(), 0) < n ? "NO" : "YES") << "\n";
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