#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, k;
  cin >> n >> k;

  string s;
  cin >> s;

  int cnt1 = count(s.begin(), s.end(), '1');
  int ans = cnt1 * 11;

  int f1 = -1, l1 = -1;
  for (int i = 0; i < n; i++) {
    if (s[i] == '1') {
      if (f1 == -1) f1 = i;
      l1 = i;
    }
  }

  if (l1 != -1 and cnt1) {
    if (k >= (n - 1) - l1) {
      k -= (n - 1) - l1;
      ans -= 10;
      cnt1--;
    }
  }

  if (f1 != -1 and cnt1) {
    if (k >= f1) {
      k -= f1;
      ans -= 1;
      cnt1--;
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