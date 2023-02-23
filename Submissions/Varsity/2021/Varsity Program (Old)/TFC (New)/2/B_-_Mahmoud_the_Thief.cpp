#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, m;
  cin >> n >> m;

  vector<int> a(n);
  map<int, int> mp;
  for (int &i : a) {
    cin >> i;
    mp[i % m]++;
  }

  vector<int> b(n);
  for (int &i : b) cin >> i, i--;

  int ans;
  for (ans = 0; ans < n - 1; ans++) {
    int r = a[b[ans]] % m;
    if (mp[r] == n - ans) break;
    mp[r]--;
    if (mp[r] == 0) mp.erase(r);
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  // cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}