#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  string s;
  cin >> s;

  int mx[2] = {0};
  for (int l = 0; l < n; ) {
    int r = l;
    while (r < n and s[r] == s[l]) r++;
    mx[s[l] - '0'] = max(mx[s[l] - '0'], r - l);
    l = r;
  }

  long long ans = max(1ll * mx[0] * mx[0], 1ll * mx[1] * mx[1]);

  ans = max(ans, 1ll * count(s.begin(), s.end(), '0') * count(s.begin(), s.end(), '1'));

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