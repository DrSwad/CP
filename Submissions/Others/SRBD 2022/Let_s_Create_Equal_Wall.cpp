#include <bits/stdc++.h>
using namespace std;

void test_case() {
  vector<int> n(3);
  for (int &i : n) cin >> i;

  vector<vector<int>> h(3);
  for (int i = 0; i < 3; i++) {
    h[i].resize(n[i]);
    for (auto &j : h[i]) cin >> j;
    h[i].push_back(0);
    reverse(h[i].begin(), h[i].end());
    for (int j = 1; j <= n[i]; j++) {
      h[i][j] += h[i][j - 1];
    }
  }

  function<bool(int)> check = [&](int H) {
    return binary_search(h[1].begin(), h[1].end(), H) and
           binary_search(h[2].begin(), h[2].end(), H);
  };

  int ans_i;
  for (ans_i = h[0].size() - 1; ans_i >= 0; ans_i--) {
    if (check(h[0][ans_i])) break;
  }

  assert(ans_i >= 0);
  cout << h[0][ans_i] << "\n";
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