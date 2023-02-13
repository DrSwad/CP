#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, m;
  cin >> n >> m;

  vector<int> till(n, -1);

  while (m--) {
    int l, r;
    cin >> l >> r;
    l--, r--;
    till[l] = max(till[l], r);
  }

  for (int l = 0; l < n; l++) {
    int prv = l == 0 ? -1 : till[l - 1];
    till[l] = max(till[l], prv);
  }

  vector<vector<int>> opens(n);
  set<int> available;
  for (int i = 0; i < n; i++) available.insert(i);
  vector<int> ans(n);

  for (int i = 0; i < n; i++) {
    ans[i] = *available.begin();
    if (till[i] >= i) {
      available.erase(available.begin());
      opens[till[i]].push_back(ans[i]);
    }
    for (int j : opens[i]) {
      available.insert(j);
    }
  }

  for (int i = 0; i < n; i++) {
    if (i) cout << " ";
    cout << ans[i] + 1;
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