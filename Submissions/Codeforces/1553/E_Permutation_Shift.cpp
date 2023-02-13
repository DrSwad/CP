#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, m;
  cin >> n >> m;

  vector<int> p(n);
  for (int &i : p) cin >> i, i--;

  auto shift = [&](int k) {
    if (k < 0) k += n;
    vector<int> q(n);
    for (int i = 0; i < n; i++) {
      int ni = i + k;
      if (ni >= n) ni -= n;
      q[ni] = p[i];
    }
    p = q;
  };

  auto cycles = [&]() {
    vector<bool> vis(n, false);
    int ans = 0;

    for (int i = 0; i < n; i++) {
      if (vis[i]) continue;

      ans++;
      for (int j = i; !vis[j]; j = p[j]) {
        vis[j] = true;
      }
    }

    return ans;
  };

  vector<int> need(n, 0);
  for (int i = 0; i < n; i++) {
    int k = i - p[i];
    if (k < 0) k += n;
    need[k]++;
  }

  vector<int> ans;
  for (int k = 0; k < n; k++) {
    if (need[k] >= n / 3) {
      shift(-k);
      int c = cycles();
      if (n - c <= m) ans.push_back(k);
      shift(k);
    }
  }

  cout << ans.size();
  for (int i : ans) cout << " " << i;
  cout << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}