#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  string s[2];
  cin >> s[0] >> s[1];

  vector<pair<int, int>> ranges;

  for (int l = 0; l < n; ) {
    if (s[0][l] != s[1][l]) {
      int r = l;
      while (r < n and s[0][r] != s[1][r]) r++;
      ranges.emplace_back(l, r);
      l = r;
    }
    else l++;
  }

  if (ranges.empty()) {
    cout << (1ll * n * (n + 1) / 2) << "\n";
  }
  else if (ranges.size() == 1) {
    cout << (2 * (n - 1)) << "\n";
  }
  else if (ranges.size() == 2) {
    cout << "6\n";
  }
  else {
    cout << "0\n";
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
