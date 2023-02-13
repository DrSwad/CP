#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> p(n);
  for (int &i : p) cin >> i;

  vector<int> ans;
  for (int l = 0, r = 0; l < n; l = r) {
    r = l;
    while (r < n and p[r] == p[l]) r++;

    if (r - l < 2) break;
    ans.push_back(r);
    for (int i = l + 1; i < r; i++) {
      ans.push_back(i);
    }
  }

  if (ans.size() != n) {
    cout << "-1\n";
  }
  else {
    for (int i = 0; i < n; i++) {
      if (i) cout << " ";
      cout << ans[i];
    }
    cout << "\n";
  }
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