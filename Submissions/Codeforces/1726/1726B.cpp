#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, m;
  cin >> n >> m;

  vector<int> ans;
  if (m < n) {}
  else if (m == n) {
    ans.resize(n, 1);
  }
  else if ((n - 1) % 2 == 0) {
    ans.resize(n - 1, 1);
    ans.push_back(m - (n - 1));
  }
  else if (m % 2 == 0 and n + 2 <= m) {
    ans.resize(n - 2, 1);
    ans.push_back((m - (n - 2)) / 2);
    ans.push_back((m - (n - 2)) / 2);
  }

  if (ans.empty()) cout << "No\n";
  else {
    cout << "Yes\n";
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