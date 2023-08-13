#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> p(n);
  for (int &i : p) cin >> i;

  int ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      int mn = min_element(p.begin() + i, p.begin() + j + 1) - p.begin();
      int mx = max_element(p.begin() + i, p.begin() + j + 1) - p.begin();
      ans += mx > mn;
    }
  }

  cout << ans << "\n";

  return 0;
}