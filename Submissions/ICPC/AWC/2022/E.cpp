#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  string s;
  cin >> s;

  for (int l = 0; l < n; ) {
    int r = l;
    while (r < n and s[r] == s[l]) r++;
    int len = r - l;
    if (len > 1 and l > 0 and r < n) {
      if (s[l] == '1') cout << l << " " << r + 1 << " " << l + 1 << " " << r << "\n";
      else cout << l + 1 << " " << r << " " << l << " " << r + 1 << "\n";
      return;
    }
    l = r;
  }

  cout << "-1\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}