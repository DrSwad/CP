#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, k;
  cin >> n >> k;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  int missing = -1;
  vector<bool> vis(n + 1, false);
  for (int i : a) vis[i] = true;
  for (int i = 0; i <= n; i++) {
    if (!vis[i]) {
      missing = i;
      break;
    }
  }

  assert(missing != -1);
  a.push_back(missing);

  vector<int> ans(n);
  for (int i = 0; i < n; i++) {
    if (i) cout << " ";
    ans[i] = a[(i - k % (n + 1) + (n + 1)) % (n + 1)];
    cout << ans[i];
  }
  cout << "\n";
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