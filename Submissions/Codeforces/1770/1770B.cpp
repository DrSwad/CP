#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, k;
  cin >> n >> k;

  vector<int> ans;
  int l = 1, r = n;
  for (int i = 0; i < n; i += 2) {
    ans.push_back(r--);
    if (i + 1 < n) ans.push_back(l++);
  }

  for (int i = 0; i < n; i++) {
    if (i) cout << " ";
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