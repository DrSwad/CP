#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, x;
  cin >> n >> x;

  string s;
  cin >> s;

  vector<int> len(n, 0);
  int sum = 0;

  for (int l = 0; l < n; ) {
    if (s[l] == '1') l++;
    else {
      int r = l;
      while (r < n and s[r] == '0') r++;
      for (int i = l; i < r; i++) len[i] = r - l;
      sum += (r - l) / x;
      l = r;
    }
  }

  int ans = sum;

  for (int i = 0; i < n; i++) {
    if (s[i] == '1') {
      int left = i == 0 ? 0 : len[i - 1];
      int right = i == n - 1 ? 0 : len[i + 1];
      int nans = sum - left / x - right / x + (left + right + 1) / x;
      ans = max(ans, nans);
    }
  }

  cout << ans << "\n";
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